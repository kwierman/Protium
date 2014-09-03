#ifndef Protium_Constructable_h_
#define Protium_Constructable_h_

#include <map>
#include <string>

namespace Protium{
	namespace Design{

		struct ConstructablePrototype{
			ConstructablePrototype(){}
			virtual ~ConstructablePrototype(){}
		};

		template<class Group>
		struct VirtualFactory{
			typedef std::map< std::string, ConstructablePrototype*(*)() > map_type;
		

			static ConstructablePrototype* createInstance(const std::string& s, ConstructablePrototype*(*creator)()=0 ){
				map_type::iterator it = getMap()->find(s);
				if( it==getMap()->end() ){
					return NULL;
				}
				return it->second();
			}
		protected:
			static map_type* getMap(){
				static map_type* map = new map_type();
				return map;
			}
		};

		template<class T, class Group>
		struct DerivedRegister : VirtualFactory<Group>{
			static ConstructablePrototype* create() {return (new T()); }
			DerivedRegister(const std::string& s ){
				getMap->insert(std::make_pair(s, &create) );
			}

		};
	}
}

#define REGISTER_DEC_TYPE(NAME) \
    static Protium::Design::DerivedRegister<NAME> reg;

#define REGISTER_DEF_TYPE(NAME) \
    Protium::Design::DerivedRegister<NAME> NAME::reg(#NAME);

#endif //File Guardian
