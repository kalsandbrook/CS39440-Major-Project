#import "template.typ": *

#set footnote(numbering: "*")

#let smallcaps(content) = {
  text(font: "Century Supra C3")[
    #content
  ]
}

#show: doc.with(
  status: "DRAFT",
  version: "v0.2",
  title: "CS39440 - GamePile",
  subtitle: "Major Project Report",
  authors: ((name: "Kal Sandbrook", email: "kas143@aber.ac.uk"),),
  supervisors: ((name: "Dr. Edore Akpokodje", email: "eta@aber.ac.uk"),),
  reference: "kas143-FinalReport",
  hasOutline: false
)

#[ <preamble> 
  #set heading(outlined: false, numbering: none)
  #page[
    #v(2fr)
    = Generative AI

    No Generative AI tools have been used for this work.

    #signatureblock()
    #v(1fr)
    = Declaration of originality

    I confirm that:
    - This submission is my own work, except where clearly indicated.
    - I understand that there are severe penalties for Unacceptable Academic Practice, which can lead to loss of marks or even the withholding of a degree.
    - I have read the regulations on Unacceptable Academic Practice from the University's Academic Registry (AR) and the relevant sections of the current Student Handbook of the Department of Computer Science.
    - In submitting this work I understand and agree to abide by the University's regulations governing these issues.

    #signatureblock()
    #v(1fr)
    = Consent to share this work

    By including my name below, I hereby agree to this project's report and technical work being made available to other students and academic staff of the Aberystwyth Computer Science Department.

    #signatureblock()
    #v(2fr)
  ]

  #page[
    #set align(center)
    #v(1fr)

    = Acknowledgements
    TODO: Add Acknowledgements - #lorem(50)

    #v(1fr)

    = Abstract // 300 words
    TODO: Write the Abstract - #lorem(295)

    #v(1fr)
  ]

  #page[
    #outline(indent: true)
  ]
]

= Background, Analysis & Process
// Discuss the topic of your project. What did the project aim to do and what did you do to investigate it?
// Look at your project diary to see what work you did early on. What resources did you read and investigate to understand the project and how did they help to define the work that you did? Resources could be books, research papers, online articles, similar software applications or other related work.
// Include references to all of those resources in the References section. Your discussion will discuss the different resources and help the reader understand the wider context for your work. As you discuss the different resources, include citations so that a reader can find more information that supports your discussion.
// The background may comment on the particular interest you have in the project and why it was something that you wanted to work on.

== Background
#wordcountsec[

=== Aims
The aim of this project was to create a native desktop application that helps users to manage their backlogs (lists of games they want to play) and libraries (games they own). The application allows users to add games to the library and mark them as part of their backlog, in progress or completed. The application will also allow users to search through their games and filter them based on various attributes such as genre, platform or completion status.

Further to this, the application will also allow users to search for games to add to their library via the use of a Third-Party API. This will use a fuzzy search algorithm to allow users to search for games even if they are unsure of the exact name. The application will also allow users to view detailed information about the games in their library, such as the aforementioned attributes.

Some optional features that could be implemented include the ability to export a users game library graphically akin to an old-school forum signature, to facilitate sharing of game completion progress on forums and social media platforms and a recommendation system that suggests games to add to the users library based on their existing library and completion status.
=== Research into Similar Tools
Initial research for this project involved investigation into similar tools that already exist. These tools were found by searching online for "game backlog manager" and "game library manager". The most popular and recommended tools were found to be websites called "How Long To Beat"@hltb and "Backloggery"@backloggery. These websites allow users to track their game completion progress and backlog, but they are web-based and do not offer a native desktop application, they are also limited to the library of games that they have in their database, not allowing for users to easily add their own games.

The research into these tools proved useful as it allowed for the mapping out of features that are essential for a backlog manager. In How Long To Beats case, the ability to track completion progress and the ability to search for games in a database were key features. Backloggery brought to light the idea of a graphical representation of a users library, which could be a unique feature to implement in this project. However, the design of the website was found to be very outdated and not visually appealing, with the sites design not having majorly changed since 2007, which could be a key area for improvement in this project, along with the performance improvements that come with a native application.
#grid(
  gutter: 2em,
  columns: (1fr,1fr),
  [
    #figure(
      caption: "A screenshot of a profile on How Long To Beat."
    )[
      #image("assets/hltb.png")
    ]
  ],
  [
    #figure(
      caption: "A screenshot of the front page of The Backloggery."
    )[
      #image("assets/backloggery.png")
    ]
  ]
)

Another technology that was investigated during development was the "Video Game Preservation Platform" Lutris@lutris - however, Lutris is more focused on game installation and management, as opposed to tracking completion and a backlog. This tool was useful for understanding how an application could be used to launch games, which could be a feature to implement in this project. The design of Lutris was also taken into account, as it contains a modern design running on a native ui framework (GTK@gtk).

#figure(
  caption: "A screenshot of the Lutris application."
)[
  #image("assets/lutris.jpg", height: 20%)
]

=== Motivation
// Base on research into similar tools, explain advantages of project over existing tools.
// Also explain interest in use of this application.

The motivation to undertake this project comes from a personal interest in the topic, as efficient tracking of game libraries and backlogs is not something readily available in the market, at least, not in a native desktop application. As existing tools are mainly web-based, they do not offer the same level of performance and integration that a native application could offer, such as being able to launch games directly from the application or being able to use the application offline.

This laid out some of the priorities for the project, such as performance improvements over existing tools, a modern and visually appealing design and the ability to be able to use the application without an internet connection. To this end, investigation into what technologies could be used to achieve these goals was undertaken.


// === Problem Overview
// === Motivation
// === Similar Tools


=== Research of UI Design
Research into UI design was conducted as a part of this project to ensure that the application was user-friendly and visually appealing. This research involved examining modern desktop applications, notably those in the KDE ecosystem, as well as inspecting the design guidelines for the Qt Framework @4cs (The "4Cs": Consistency, Continuity, Context and Complementary being considered throughout design iterations.)  and the KDE Human Interface Guidelines@kdehig (which can be summarised as "Simple by default, Powerful when needed.")

These principles promote reusing design patterns from other applications so that users can easily understand how to use the application, and that complex tasks should feel simple to the user. This research was used to inform the design of the application during development, ensuring a intuitive and user-friendly experience.

=== Options for Third-Party API

For the API module of the project, a third-party API was required to allow users to fetch game data from the internet. Ideally, this API would allow for searching for games by name and return detailed information about the game - at the very least, the release date, genre, platform and a description of the game. 

This API would also need to be free to use, and preferably not involve a complicated authentication process to access the data (such as having to sign up for an API key). Appropriate Licensing is also a consideration, as the API will be used in an educational capacity.

Two initial options were IGDB@igdbdocs (Internet Game Database) and the Steam Web API. The IGDB API was ruled out as it requires the user to have a #link("https://twitch.tv/")[Twitch] account in order to sign up for an API key - which would require functionality that is out of scope for this project, requiring the application to sign up with the _Twitch Developers_ system.

The Steam Web API does not require any authentication to access the data, and was found to be a good option for this project. The API does not support searching, but a list of games can be obtained and searched through locally. Steam Web API also provides information of a requisite level of detail for this project.
]

#pagebreak(weak:true)

== Analysis 
// Having established the background, write about your analysis of the problem and what that meant for the work that needed to be done. What was the problem to be solved or researched? What did you do to identify and analyse the requirements for the work? Discuss how your analysis was used to decompose the problem into different units of work.
// Think about any alternative approaches that you investigated. What that means will vary by the type of project you are working on. It will probably include an assessment of the relevant technologies but it is likely to be wider than that. Issues such as data representation, processing issues and communications protocols are examples of other things that might be relevant.
// You are not explaining the solutions in this section because you will discuss that in later sections. Here, you are analysing and decomposing the problem.
// Clearly identify the objectives of the work. For an engineering project this is typically as a set of requirements. For a research project this is a statement of the research questions and the requirements for the supporting software you will create. You will evaluate your outcomes against those objectives later in the report. See Requirements for some additional guidance.
// In most cases, the agreed objectives or requirements will be the result of a compromise between what would ideally have been produced and what was determined to be possible in the time available. A discussion of the process of arriving at the final list is usually appropriate.

#wordcountsec[

Whilst this project may seem simple on the surface, there are a number of considerations to be made. Firstly, the scope of the project had to be defined. The project was split into two main components - the main application and the API module. The main application would be responsible for managing the users library and backlog, whilst the API module would be designed to fetch game data from the internet. If the social features and recommendation system were to be implemented, they would be a part of the main application - although likely in seperate modules.

=== Identification of Requirements and Objectives

The requirements for this project were identified through the research conducted in the background section. As a significant portion of the other tools investigated were web-based, there are considerations this project had to make which are not relevant for web-based apps. The key requirements for the project were as follows:

- The application must allow users to add games to their library and mark them as part of their backlog, in progress or completed.
- The application must allow users to search through their games and filter them based on various attributes.
- The application must allow users to search for games to add to their library via the use of a Third-Party API.
- The application must allow users to view detailed information about the games in their library, such as the aforementioned attributes.
- The application must be visually appealing and user-friendly, following modern design principles.
- The application must be performant, able to stand up even with a very large library of games.

These Requirements are discussed in more detail in @Requirements.

=== Choice of Technologies

// Mention that choice of language was considered up until the beginning of development, along with some testing of each language to test suitability. 

The choice of language for this project was a matter of consideration up until the beginning of development. The two main languages considered were C++ and Python, and were the two languages used in the development of this project. 

C++ was chosen for the main application due to its unrivalled performance, high suitability for Object-Oriented problems and, via use of the Qt@qt platform, a native and robust UI framework. Python was chosen for the API module due to its excellent networking libraries and ease of use, along with its libraries for fuzzy string matching.

The Qt Framework also boasts an extensive range of documentation and tutorials available online, making it an attractive choice for this project. It also has cross-platform capabilities, allowing the application to be shipped on the _Windows_, _MacOS_ and _Linux_ operating systems. #footnote[However, the project was developed with a focus on Linux compatibility, with support for other operating systems coming second.]

Another advantage of using Python for the API module is that it allows for easy packaging of the module into an executable, which can be used standalone of the main program, allowing for easy testing and debugging of the module. This was achieved using the pyinstaller@pyinstaller library.

Finally, the method of persistent data storage had to be considered. Due to the nature of the data being stored, a relational database was chosen as the method of storage, in particular an SQLite database, due to its lightweight nature and ease of use. In a bigger project, a more robust database system such as PostgreSQL could be considered.
=== Alternative Approaches

// Rust - no mature UI tooling - maybe a cursory mention to areweguiyet (as a footnote) - using Qt bindings wouldnt be worth it as it's essentially coding in C++ at that point.
// Fully Python - Slow
Many other languages were considered for this project, such as an entirely Python-based solution. However, Python does not have the same level of performance as C++, and would not fulfil the performance objectives of the project. Python also does not have an object-oriented system that is as robust as C++, which would make the project harder to maintain and increase the difficulty of debugging the application.

Another language that was considered for this project was the increasingly popular Rust language. Rust is known for its performance and rigorous safety requirements, which would have made it a good choice for a project such as this. However, a significant caveat to using Rust for this project is the lack of a mature UI tooling ecosystem. Whilst there are bindings (bindings being a way to use a library from another language) for Qt in Rust, this would essentially involve doing the majority of the work in C++ regardless, which would defeat the purpose of using Rust in the first place.

Java and C\# were also considered, but were ruled out - Java due to its performance and C\# due to the impracticality of using it on Linux systems. Java also has an absence of modern UI tooling, with Swing and JavaFX being the only real options, both of which are outdated and not visually appealing. QtJambi was briefly investigated as a potential solution, but there was found to be a lack of documentation and community support for the library.

]
== Process 
// Describe the life cycle model or research method that you used. You do not need to write about all of the different process models that you are aware of. Focus on the process model that you have used and why you chose it. It is likely that you needed to adapt an existing process model to suit your project; clearly identify what you used and how you adapted it for your needs.
When planning development, a Kanban framework was used to manage the project. The use of a Kanban Board is a common practice in software development, and one of the few practices that can be used for a solo project. 

The Kanban Board was used to manage the project by decomposing the project down into smaller tasks and assigning them to one of three (although there are four columns in total) columns on the board. The columns were "To Do", "In Progress" and "Done". The "To Do" column contained all tasks that needed to be completed, with cards sorted by priority; the "In Progress" column contained tasks that were currently being worked on; and the "Done" column contained tasks that had been completed. A WIP Limit was set so only three tasks could be deemed to be "In Progress" at any one time, to prevent jobs from being left unfinished.

Using the "GitHub Projects" feature to host the Kanban Board, the project was able to be effectively managed. Using this feature allowed issues to be linked to cards on the board, which allowed for easy tracking of progress and completion of tasks. 

When Functional Requirements were identified, they were added as issues to the GitHub repository and linked to cards on the Kanban board, serving as small milestones. Cards were also labelled with the type of task they were such as "Feature", "Bug" or "Documentation".

Certain cards were linked to larger milestones, such as the Mid-Project Demonstration, clearly showing what features I wanted to have in place by that point. This allowed for a clear plan in regards to the timing of the project, and what features were to be implemented.

#figure(
  caption: "A screenshot of the GitHub Projects board used for this project."
)[
  #image("assets/kanbanboard.png", width: 100%)
]

// Could expand on other methodologies considered and why they were not chosen.

A weekly log has been kept throughout the project to document progress and any issues that arose. Each week was broken up into the objectives for the week, the tasks completed, the challenges faced and the plans for the upcoming week. This log was used primarily as a starting point for the weekly meetings with the project supervisor, it also served as a good way to keep track of progress and the pace of development.

// TODO: Should weekly logs be included in the appendices?
= Requirements <Requirements>

// Use-Case Diagram

= Design 

= Implementation

== Class Diagram

// Entity Relationship Diagram

= Testing // 1,500 words

= Evaluation // 1,500 words

#pagebreak()

#bibliography("bibliography.yml", style: "ieee-notes.csl", full: true)

#pagebreak()


#heading(numbering: "1")[Appendices]

#[ <appendices>
  #appendix(title: [Appendix A -- Third-Party Code and Libraries])[
  #set heading(outlined: false)
  === Qt @qt

  The Qt Framework (particularly Qt Widgets) was used for the majority of development for this project. It provides a wide variety of features - notably its Qt Widgets, Qt SQL & Qt Concurrent modules.

  For academic purposes, Qt Community Edition (the edition used for development) follows the _GNU Lesser General Public License_ ("(L)GPL"), a copy of which can be accessed here: #link("https://www.gnu.org/licenses/lgpl-3.0.txt")

  No tools such as Qt Creator or Qt Designer were used in development.

  === Python Libraries

  For the API module of the project, Python was used due to its excellent range of libraries. The following libraries were used:
  - _Requests_ @requests
    - Used for making HTTP requests to the API.
  - _TheFuzz_ @thefuzz
    - Used for fuzzy string matching, particularly using the jaro-winkler algorithm.
  - _PyInstaller_ @pyinstaller
    - Used for packaging the API module into an executable.
  ]
]