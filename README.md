# library-management-system-c++
using TCP IP server client communication and writing unit test cases using boost library.

SETUP:
Download boost 1.64.0 from here http://www.boost.org/users/download/
Extract it (e.g cd C:\yoursystem\Boost) like this anywhere in your system
Open command prompt change to boost directory (e.g cd:c:\yoursystem\Boost)
Execute .\bootstrap.bat (Note it will take some time)
Execute .\b2 -j8 --toolset=msvc-14.0 address-model=64 --build-type=complete stage 
thenboost setup is done.
Now open Visual studio 2015 and clone the project.
open properties of "client" and "server" and go to 
C\C++ --> general-->additional include directories as (e.g \yoursystem\boost_1_64_0), 
      -->precompiled headers --> Precomplied headers as Not using precompiled headers.
Linker -->general-->Additional library directorie as (e.g \yoursystem\boost_1_64_0\stage\x64\lib)
Now open properties of "Unit testing" and go to
C\C++ --> general-->additional include directories as (e.g \yoursystem\boost_1_64_0), 
      -->precompiled headers --> Precomplied headers as Not using precompiled headers.
Linker -->general-->Additional library directorie as (e.g \yoursystem\boost_1_64_0\stage\lib)

Now Build solution and execute.
