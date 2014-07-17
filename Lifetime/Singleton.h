


	    template <class T>
    	class PhoenixSingleton{
	    public:
    	    static void ScheduleDestruction(T*, atexit_pfn_t pFun){
            if (!destroyedOnce_)
                std::atexit(pFun);
	        }
	        static void OnDeadReference(){
	            destroyedOnce_ = true;
	        }
	    private:
	        static bool destroyedOnce_;
	    };

	    template <class T> bool PhoenixSingleton<T>::destroyedOnce_ = false;


	    template <class T>
	    class DeletableSingleton
	    {
	    public:

	        static void ScheduleDestruction(T*, atexit_pfn_t pFun)
	        {
	            static bool firstPass = true;
	            isDead = false;
	            deleter = pFun;
	            if (firstPass || needCallback)
	            {
	                std::atexit(atexitCallback);
	                firstPass = false;
	                needCallback = false;
	            }
	        }
	    
	        static void OnDeadReference()
	        { 
	        }
	        ///  delete singleton object manually
	        static void GracefulDelete()
	        {
	            if (isDead)
	                return;
	            isDead = true;
	            deleter();
	        }
	    
	    protected:
	        static atexit_pfn_t deleter;
	        static bool isDead;
	        static bool needCallback;
	        
	        static void atexitCallback()
	        {
	            needCallback = true;
	            GracefulDelete();
	        }
	    };

	    template <class T>
	    atexit_pfn_t DeletableSingleton<T>::deleter = 0;
	    
	    template <class T>
	    bool DeletableSingleton<T>::isDead = true;
	    
	    template <class T>
	    bool DeletableSingleton<T>::needCallback = true;


        template <class T>
        struct Adapter
        {
            void operator()(T*) { return pFun_(); }
            atexit_pfn_t pFun_;
        };

		template <class T>
	    class SingletonWithLongevity
	    {
	    public:
	        static void ScheduleDestruction(T* pObj, atexit_pfn_t pFun)
	        {
	            Adapter<T> adapter = { pFun };
	            SetLongevity(pObj, GetLongevity(pObj), adapter);
	        }
	        
	        static void OnDeadReference()
	        { throw std::logic_error("Dead Reference Detected"); }
	    };

		template <class T>
	    struct NoDestroy
	    {
	        static void ScheduleDestruction(T*, atexit_pfn_t)
	        {}
	        
	        static void OnDeadReference()
	        {}
	    };

		template <unsigned int Longevity, class T>
        class SingletonFixedLongevity
        {
        public:
            virtual ~SingletonFixedLongevity() {}
            
            static void ScheduleDestruction(T* pObj, atexit_pfn_t pFun)
            {
                Private::Adapter<T> adapter = { pFun };
                SetLongevity(pObj, Longevity , adapter);
            }
            
            static void OnDeadReference()
            { throw std::logic_error("Dead Reference Detected"); }
        };

        template <class T>
        struct DieLast  : SingletonFixedLongevity<0xFFFFFFFF ,T>
        {};

        ///  \struct DieDirectlyBeforeLast
        ///  \ingroup LongevityLifetimeGroup
        ///  \brief  Lifetime is a one less than DieLast: 0xFFFFFFFF-1
        template <class T>
        struct DieDirectlyBeforeLast  : SingletonFixedLongevity<0xFFFFFFFF-1 ,T>
        {};

        ///  \struct DieFirst
        ///  \ingroup LongevityLifetimeGroup
        ///  \brief  Shortest possible SingletonWithLongevity lifetime: 0 
        template <class T>
        struct DieFirst : SingletonFixedLongevity<0,T>
        {};




            class FollowIntoDeath
    {
        template<class T>
        class Followers
        {
            typedef std::vector<atexit_pfn_t> Container;
            typedef typename Container::iterator iterator;
            static Container* followers_;
        
        public:
            static void Init()
            {
                static bool done = false;
                if(!done)
                {
                    followers_ = new Container;
                    done = true;
                }
            }

            static void AddFollower(atexit_pfn_t ae)
            {
                Init();
                followers_->push_back(ae);
            }

            static void DestroyFollowers()
            {
                Init();
                for(iterator it = followers_->begin();it != followers_->end();++it)
                    (*it)();    
                delete followers_;
            }
        };

    public:

        ///  \struct With
        ///  Template for the master 
        ///  \param Lifetime Lifetime policy for the master
        template<template <class> class Lifetime>
        struct With
        {
            ///  \struct AsMasterLifetime
            ///  Policy for master
            template<class Master>
            struct AsMasterLifetime
            {
                static void ScheduleDestruction(Master* pObj, atexit_pfn_t pFun)
                {
                    Followers<Master>::Init();
                    Lifetime<Master>::ScheduleDestruction(pObj, pFun);

                    // use same policy for the followers and force a new 
                    // template instantiation,  this adds a additional atexit entry
                    // does not work with SetLonlevity, but there you can control
                    // the lifetime with the GetLongevity function.
                    Lifetime<Followers<Master> >::ScheduleDestruction(0,Followers<Master>::DestroyFollowers);
                }

                static void OnDeadReference()
                { 
                    throw std::logic_error("Dead Reference Detected"); 
                }
            };
        };

        ///  \struct AfterMaster
        ///  Template for the follower
        ///  \param Master Master to follow into death
        template<class Master>
        struct AfterMaster
        {
            ///  \struct IsDestroyed
            ///  Policy for followers 
            template<class F>
            struct IsDestroyed
            {
                static void ScheduleDestruction(F*, atexit_pfn_t pFun)
                {
                    Followers<Master>::AddFollower(pFun);
                }
      
                static void OnDeadReference()
                { 
                    throw std::logic_error("Dead Reference Detected"); 
                }
            };
        };
    };

    template<class T>
    typename FollowIntoDeath::Followers<T>::Container* 
    FollowIntoDeath::Followers<T>::followers_ = 0;
    
    
    
    ////////////////////////////////////////////////////////////////////////////////
    ///  \class  SingletonHolder
    ///
    ///  \ingroup SingletonGroup
    ///
    ///  Provides Singleton amenities for a type T
    ///  To protect that type from spurious instantiations, 
    ///  you have to protect it yourself.
    ///  
    ///  \param CreationPolicy Creation policy, default: CreateUsingNew
    ///  \param LifetimePolicy Lifetime policy, default: DefaultLifetime,
    ///  \param ThreadingModel Threading policy, 
    ///                         default: LOKI_DEFAULT_THREADING_NO_OBJ_LEVEL
    ////////////////////////////////////////////////////////////////////////////////
    template
    <
        typename T,
        template <class> class CreationPolicy = CreateUsingNew,
        template <class> class LifetimePolicy = DefaultLifetime,
        template <class, class> class ThreadingModel = ClassLevelLockable,
        class MutexPolicy = Mutex
    >
    class SingletonHolder{
    public:

        ///  Type of the singleton object
        typedef T ObjectType;

        ///  Returns a reference to singleton object
        static T& Instance();
        
    private:
        // Helpers
        static void MakeInstance();
        static void DestroySingleton();
        
        // Protection
        SingletonHolder();
        
        // Data
        typedef typename ThreadingModel<T*,MutexPolicy>::VolatileType PtrInstanceType;
        static PtrInstanceType pInstance_;
        static bool destroyed_;
    };
    
    ////////////////////////////////////////////////////////////////////////////////
    // SingletonHolder's data
    ////////////////////////////////////////////////////////////////////////////////

    template
    <
        class T,
        template <class> class C,
        template <class> class L,
        template <class, class> class M,
        class X
    >
    typename SingletonHolder<T, C, L, M, X>::PtrInstanceType
        SingletonHolder<T, C, L, M, X>::pInstance_ = 0;

    template
    <
        class T,
        template <class> class C,
        template <class> class L,
        template <class, class> class M,
        class X
    >
    bool SingletonHolder<T, C, L, M, X>::destroyed_ = false;

    ////////////////////////////////////////////////////////////////////////////////
    // SingletonHolder::Instance
    ////////////////////////////////////////////////////////////////////////////////

    template
    <
        class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class, class> class ThreadingModel,
        class MutexPolicy
    >
    inline T& SingletonHolder<T, CreationPolicy, 
        LifetimePolicy, ThreadingModel, MutexPolicy>::Instance()
    {
        if (!pInstance_)
        {
            MakeInstance();
        }
        return *pInstance_;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // SingletonHolder::MakeInstance (helper for Instance)
    ////////////////////////////////////////////////////////////////////////////////

    template
    <
        class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class, class> class ThreadingModel,
        class MutexPolicy
    >
    void SingletonHolder<T, CreationPolicy, 
        LifetimePolicy, ThreadingModel, MutexPolicy>::MakeInstance()
    {
        typename ThreadingModel<SingletonHolder,MutexPolicy>::Lock guard;
        (void)guard;
        
        if (!pInstance_)
        {
            if (destroyed_)
            {
                destroyed_ = false;
                LifetimePolicy<T>::OnDeadReference();
            }
            pInstance_ = CreationPolicy<T>::Create();
            LifetimePolicy<T>::ScheduleDestruction(pInstance_, 
                &DestroySingleton);
        }
    }

    template
    <
        class T,
        template <class> class CreationPolicy,
        template <class> class L,
        template <class, class> class M,
        class X
    >
    void LOKI_C_CALLING_CONVENTION_QUALIFIER 
    SingletonHolder<T, CreationPolicy, L, M, X>::DestroySingleton()
    {
        assert(!destroyed_);
        CreationPolicy<T>::Destroy(pInstance_);
        pInstance_ = 0;
        destroyed_ = true;
    }


    ////////////////////////////////////////////////////////////////////////////////
    ///  \class  Singleton
    ///
    ///  \ingroup SingletonGroup
    ///
    ///  Convenience template to implement a getter function for a singleton object.
    ///  Often needed in a shared library which hosts singletons.
    ///  
    ///  \par Usage
    ///
    ///  see test/SingletonDll
    ///
    ////////////////////////////////////////////////////////////////////////////////

#ifndef LOKI_SINGLETON_EXPORT
#define LOKI_SINGLETON_EXPORT
#endif

    template<class T>
    class LOKI_SINGLETON_EXPORT Singleton
    {
    public:
        static T& Instance();
    };

} // namespace Loki


/// \def LOKI_SINGLETON_INSTANCE_DEFINITION(SHOLDER)
/// Convenience macro for the definition of the static Instance member function
/// Put this macro called with a SingletonHolder typedef into your cpp file.

#define LOKI_SINGLETON_INSTANCE_DEFINITION(SHOLDER)                     \
namespace Loki                                                          \
{                                                                        \
    template<>                                                          \
    SHOLDER::ObjectType&  Singleton<SHOLDER::ObjectType>::Instance()    \
    {                                                                   \
        return SHOLDER::Instance();                                     \
    }                                                                    \
}