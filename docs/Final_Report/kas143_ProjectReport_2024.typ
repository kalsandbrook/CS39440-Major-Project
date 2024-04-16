#import "template.typ": *


#let smallcaps(content) = {
  text(font: "Century Supra C3")[
    #content
  ]
}

#show: doc.with(
  status: "DRAFT",
  version: "v0.1",
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
    = Generative AI

    No Generative AI tools have been used for this work.

    #signatureblock()
    
    = Declaration of originality

    I confirm that:
    - This submission is my own work, except where clearly indicated.
    - I understand that there are severe penalties for Unacceptable Academic Practice, which can lead to loss of marks or even the withholding of a degree.
    - I have read the regulations on Unacceptable Academic Practice from the University's Academic Registry (AR) and the relevant sections of the current Student Handbook of the Department of Computer Science.
    - In submitting this work I understand and agree to abide by the University's regulations governing these issues.

    #signatureblock()

    = Consent to share this work

    By including my name below, I hereby agree to this project's report and technical work being made available to other students and academic staff of the Aberystwyth Computer Science Department.

    #signatureblock()

    = Acknowledgements
  ]

  #page[
    = Abstract // 300 words
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
== Analysis 

=== Identification of Requirements
=== Data Storage
=== User Interface
=== Performance

== Process 

= Requirements

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


  #heading[Appendices]
#[ <appendices>
  #set heading(numbering: none)
  == Appendix A --- Third-Party Code and Libraries
  #[
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