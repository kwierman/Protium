Protium
----------------------

Framework and primitive definitions for Tritium libraries


#Notes On Dimensional Analysis

Tritium Implements a system of meaningful dimensional analysis.

This supports conversion between dimensions using the `*` and `/` operators.

Therefore the folling should compile:
```C++
Protium::Design::Scalar scaler =Rate(1.0)*Time(1.0);//This works
Protium::Design::Action act =	Energy(20.0)*Time(5.0);//Also works
```
This should not:
```c++
TriScalar doesntWork = TriTime(0.0)*TriTime(0.0); //This doesn't work
```
This produces the following compile-time error:
```python
error: invalid use of incomplete type ‘struct CompileTimeError<0>’
             ERROR_QUANTITIES_NOT_EQUAL_DIMENSIONS() );
```