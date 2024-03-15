#import "@preview/polylux:0.3.1": *

#set page(paper: "presentation-16-9")
#set text(
	font: "Century Supra T4", 
	size:22pt,
	fill: luma(35),
	)

#let smallcaps(content) = [
	#set text(font: "Century Supra C4")
	#content
]

#polylux-slide[
	#align(horizon + center)[
		\
		#set text(size: 25pt)
		#heading(level: 1)[GamePile]
		#smallcaps[Tool for organising Video Games]	
	]
	#align(center)[
		Mid-Project Demonstration
		
		_Kal Sandbrook [kas143]_
		
		\
		\
		March 15th, 2024
	]
]

#polylux-slide[
	== A Brief Description	

	GamePile is an application which helps users keep track of their video game libraries, allowing for efficient organisation.

	== Aims

	- Allow users to store information on their library of video games.
	- Mark games as "Abandoned", "Completed", "Backlogged", etc. 
	- The use of a third-party API to add video games into the library.

	==== Optionally...
	- Export a graphical overview of completed games.
	- Research and potentially implement an algorithm which recommends user games they may enjoy.
]

#polylux-slide[
	== Methodology

	- Focus on using _GitHub Issues_ as a Kanban Board to track progress

	- Use of a weekly log, laying out the tasks for each week and providing an agenda of what to discuss at weekly meetings.

	- Continuous Integration via GitHub Actions for building & testing

	#columns(2)[
	#image("kanban-board.png",height: 40%)
	#image("weekly-log-excerpt.png")
	]

	// Not strict adherence to agile method
	// Mention CI, Living Documentation via Doxygen, Kanban Board & Weekly Log
]

#polylux-slide[
	#grid(
		columns: (1fr,1fr)
	)[
	== Progress
	// Detail summary of functional requirements and specify rough timeline??
		- The application currently has a _prototype UI_, allowing users to add and edit games.

		- Basic filtering is supported, with the underlying code for more advanced filtering in place.
	][
		=== Next Steps

		- Add more fields for games, adhereing to the structure in the Database Schema.

		- Add support for getting game information from an API.

		- Another pass on the UI ahead of final submission, polishing up the application.
	]
]

#polylux-slide[
#align(center+horizon)[
	#image("application.png")
	]
]

#polylux-slide[
	#set text(size: 20pt)
	== Technologies Involved

	// C++, Qt, Cmake + doxygen and mention of Qt Testing
	- C++ (Programming Language)
		- Performant and powerful language.
		- Problem well suited for Object-Oriented solution.
	- Qt (UI Library)
		- Well documented, with good support for multiple operating systems.
		- Faster than web-based solution.
		- Notable uses include the K Desktop Environment (KDE).
	- CMake (Build System)
	- Typst (Typesetting & Documentation)
		- A "modern LaTeX" alternative.
	- Doxygen for generating LaTeX / HTML Documentation from source code comments.
]

// #polylux-slide[
// 	== Conclusion
// 	// A summary of the contents of the document
// ]