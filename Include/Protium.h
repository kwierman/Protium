/*!
	\mainpage The Protium Libraries

	\tableofcontents

	\section intro Introduction

	This is the placeholder simulation for Neutron Flux at low depths (NeutronFlux, or NeuFlux for short).
	The prupose of this software is to 
	
	\section downloading Downloading Software

	This software is hosted on <a href="https://github.com/">GitHub</a>. 
	The URL for the repository is: https://github.com/kwierman/Protium .

	Pulling from the repository can be accomplished by downloading <a href="https://github.com/">Git</a>
	
	~~~~~~~~~~~~~~~~~~~~~
	git clone https://github.com/kwierman/Protium.git
	~~~~~~~~~~~~~~~~~~~~~

	It is advisable that if the software is being worked on to create a separate branch. 
	This can be accomplished with the following line:

	~~~~~~~~~~~~~~~~~~~~~
	git checkout -b <your_branch_name>
	~~~~~~~~~~~~~~~~~~~~~

	Pushing to the repository can be accomplished with the following command:

	~~~~~~~~~~~~~~~~~~~~~
	git push -u origin <your_branch_name>
	~~~~~~~~~~~~~~~~~~~~~

	---

	\section dep Dependencies

	The following libraries must be built and in the paths in order to build properly:

	-  CMake
		- <a href="http://www.cmake.org/">CMake Website</a>
		- Required for building the program


	---

	\section building Building

	In order to generate build files for the program, issue the following command:

	~~~~~~~~~~~~~~~~~~~~~
	cmake <directory where code resides>
	~~~~~~~~~~~~~~~~~~~~~

	Or, to use the graphical editor:

	~~~~~~~~~~~~~~~~~~~~~
	ccmake <directorys where the code resides>
	~~~~~~~~~~~~~~~~~~~~~
	
	If configuring cmake and generating build files 

	\subsection nix_build Unix-Like Systems

	This includes MacOSX (Darwin).
	The commands to issue at this point are:

	~~~~~~~~~~~~~~~~~~~~~
	make
	make install
	~~~~~~~~~~~~~~~~~~~~~

	Make sure to set `LD_LIBRARY_PATH` or, on Darwin, `DYLD_LIBRARY_PATH` to the location of the libraries

	\subsection windows_build Windows

	Open the build solution in windows by either clicking on `Protium.vcproj`, or opening 'Visual Studio' and open the solution 'Protium'.

	Once Visual Studio has ompleted parsing the documents, navigate `Solution->Build->Release` or hit the green arrow.

	---
	\section running Running

	Protium will include unit tests

	~~~~~~~~~~~~~~~~~~~~~
	<name of exec> <optional path to macro>
	~~~~~~~~~~~~~~~~~~~~~

	The source code for the main executables is found in the Applications/ folder
	
	---

	\section code_hierarchy Code Hierarchy

	All necessary headers are included in the top-down file, Protium.h .

	---

	\section contact Contact

	Please contact Kevin Wierman at kwierman@email.unc.edu with issues, flaws or questions
*/

/** \file Protium.h
	\author Kevin Wierman
	\email kwierman@gmail.com
	\breif Umbrella include file for all of the protium libraries
**/
#ifndef Protium_h_
#define Protium_h_



#include "Protium/LinearAlgebra/LinearAlgebra.h"

//! Umbrella namespace for Protium Libraries
namespace Protium{}

#endif