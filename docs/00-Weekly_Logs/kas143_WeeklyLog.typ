#import "template.typ": doc

#show: doc.with(
  //status: "RELEASE",
  //version: "v1.0",
  title: "CS39440: Weekly Logs",
  subtitle: "GamePile",
  authors: ((name: "Kal Sandbrook", email: "kas143@aber.ac.uk"),),
  supervisors: ((name: "Dr. Edore Akpokodje", email: "eta@aber.ac.uk"),),
  reference: "kas143_WeeklyLogs",
)

#let week(
  weekCommencing: [],
  focus: none, // A short focus for the heading
  objectives: none, // A paragraph describing the objective for the week
  tasks: none, // A bulleted list that describes the *completed* tasks that week
  challenges: none, // Challenges faced that week
  plans: none, // Plans for the next week
  additional: none, // Any additional notes
) = {
  block( {
    heading(level: 1, numbering: "Week 1")[-- W/C: #weekCommencing --- #focus]

    if(objectives != none){
      heading(level: 2)[Week's Objectives]
      objectives
    }

    if(tasks != none){
      heading(level: 2)[Completed Tasks]
      tasks
    }

    if(challenges != none){
      heading(level: 2)[Challenges Faced]
      challenges
    }

    if(plans != none){
      heading(level: 2)[Plans for Next Week]
      plans
    }

    if(additional != none){
      heading(level: 2)[Additional Notes]
      additional
    }
  }
  )
  pagebreak(weak:true)
}


#week(
  weekCommencing: "29th January",
  focus: "Project Initiation",
  objectives:
  [
    The objectives for the first week of the project are to decide on the specifics of development. To this end, a project outline will be produced in order to determine: the development methodology going forward, initial research to be carried out, the scope of the project and the platform development will be performed on.
  ],
  tasks:
  [
    1. Initial Research
      - Initial research was carried out on competing applications that offer similar features to the ones proposed by the project. Two of these competitors are #link("https://www.backloggd.com/")[Backloggd] and #link("https://howlongtobeat.com/")[HowLongToBeat].
    2. Document Template Created
      - A template for the typesetting system #link("https://typst.app/")[Typst] was devised in order to produce the official documents for this project.
  ],
  challenges: 
  [
    Finding an appropriate platform for development was initially challenging. Most "powerful" modern UI toolkits are web-based in some way, and one of the goals of the project is to provide a solution that uses a native UI library. Some research into appropriate programming languages has been detailed in `kas143-LanguageSelection`.
  ],
  plans:
  [
    Plans for Week 2 include further development of the project outline and completion of the Language Selection report showcasing different options regarding development.
  ]

)

#week(
  weekCommencing: "5th February",
  focus: "Project Outline and Preperation",
  objectives:
  [
    This weeks focus is on finishing the project outline and selecting a programming language. By finishing the outline, a development methodology and environment could be established - allowing for the start of development.
  ],
  tasks:
  [
    1. Project Outline Completed
      - The project outline has been completed, this document will provide a good framework for what the project sets out to do. 
    2. Language Selection Document
      - A document was produced weighing up the advantages of different programming languages that could be used in the project. A final decision is yet to be reached.
    3. GitHub Repository Created
      - A private GitHub repository has been created to host the source code for the project. It will also host the source files for documentation, including this document.
  ],
  challenges:
  [
    Deciding on a programming language is still proving to be difficult. Cursory looks at Python (PyQt) and QtJambi were not promising. In my view, Python's syntax is too simple for a project of this scope, whilst QtJambi seems to not have very active development and setting up a development environment for it proved troubling.
  ],
  plans:
  [
    Next week, a Requirements Analysis will be produced. This will allow for development to properly start under the Kanban methodology, where each functional requirement is used as a "card" in order to track development.

    A final decision regarding a programming language will also have to be made.
  ]
  )

#week(
  weekCommencing: "12th February",
  focus: "Requirements and Development Begins",
  objectives:
  [
    This week will result in a final choice of programming language (likely C++) and the beginning of development. The aim is to build a prototype application that displays a list of Objects and develop the project from that prototype upwards.

    This will also require setting up a development environment.
  ],
  tasks:
  [
    1. Final Decision on Programming Language
      - It has been decided that C++ will be the programming language used for this project. The Qt UI Toolkit will also be used.
    2. Setup of Development Environment
      - A development environment has been set up using: #link("https://www.jetbrains.com/help/clion/clion-nova-introduction.html")[CLion Nova] on Microsoft Windows, using the Clang Compiler with the Ninja build system.
    3. Continuous Integration
      - A GitHub workflow has been set up so when a commit is uploaded to the GitHub repository, it test to see if the source code successfully builds. This will be expanded to include testing in coming weeks.
  ],
  challenges:
  [
    Qt has a significant learning curve that I could have been better prepared for. However, steady progress is being made, although initial development may be slower due to the time spent reading documentation and tutorials. #footnote[https://doc.qt.io/ - specific documentation pages have been recorded and will be included with the report.]

    I have also encountered an issue with the application crashing on Windows for no obvious reason. Further investigation pending.
  ],
  plans:
  [
    Next week will see the production of a database schema and hopefully the implementation of FR01 (basic CRUD functionality). 
  ]
)

#week(
  weekCommencing: "19th February",
  focus: "Initial Development Complications",
  objectives:
  [
    The aims of this week are to increase my proficiency with C++ and Qt, to complete FR01 and start working towards a prototype that is appropriate for the Mid-Project Demonstration. A class diagram will also be produced this week.
  ],
  tasks: 
  [
    1. Learning C++ Qt (using Documentation)
      - I worked my way through #link("https://learncpp.com/") in order to be better prepared for further development. I also looked through some example projects provided as part of the Qt documentation. These were:
        - #link("https://doc.qt.io/qt-6/qtwidgets-dialogs-standarddialogs-example.html")[Standard Dialogs]
        - #link("https://doc.qt.io/qt-6/qtwidgets-richtext-orderform-example.html")[Order Form Example]
        - #link("https://doc.qt.io/qt-6/qtdoc-demos-documentviewer-example.html")[Document Viewer]
    2. Class Diagram
      - A class diagram was produced. This is good for avoiding going into development "blind", and to visually explain the structure to those trying to understand the system.
    3. Change of OS for Development
      - Due to an issue with my Qt Environment on windows, I switched to developing on Linux.
    4. Rewrite of Project Code
      - The initial code did not have a very cohesive structure, so I started from scratch.
  ],
  challenges:
  [
    The bug with Qt crashing on Windows took up a lot of development time, and no obvious cause has yet been identified. Combined with Illness, this led to the amount of work produced this week to be below expectations.

    Regarding the change of OS, Cross-Compilation #footnote[Compiling the program on Linux, to be run on Windows.] will be investigated later into the project.
  ],
  plans:
  [
    Next week, a database will be incorporated into the application and FR01 will be fulfilled.
  ]
)

#week(
  weekCommencing: "26th February",
  focus: "FR01 and Gaining Momentum",
  objectives:
  [
    This week's objectives are to complete FR01. Last week and the beginning of this week resulted in a complete change of how the program is structured, so whilst development has been slow (in terms of deliverables and visible progress) - it is anticipated that development will speed up significantly going forward.
  ],
  tasks:
  [
    1. Database Schema
      - A database schema showing a rough implementation of how the database could be implemented was produced.
    2. Data Persistence
      - The application now uses an SQLite Database in order to maintain persistent data when restarting the application.
    3. Code Documentation Generation (doxygen)
      - #link("https://www.doxygen.nl")[doxygen] is a documentation generator that is similar to JavaDoc. It is being used to extract comments from the source code of the program and display those comments in a presentable way. The documentation produced will be included in the appendix of the project report.
      - doxygen has also been set up with GitHub's Continuous Integration system, updating the documentation with every commit pushed to the repository. A HTML Version of the documentation is available #link("https://kalsandbrook.github.io/CS39440-Major-Project/")[here].
    4. FR01 - Game Management
      - Games can now be added, deleted and edited within the application. This is currently in a limited capacity, but more fields will become available when the UI is updated (thus fulfilling FR05).
  ],
  challenges:
  [
    Whilst development is now starting to pick up, a lot of classes are being revised as a part of adding features. Documents that describe program structure (such as Class Diagrams) may need to be revised throughout development.
  ],
  plans:
  [
    As the Mid-Project demonstration is approaching, the intent is to finish FR02, FR03 and FR04. Whilst this initially appears to be a large undertaking for a single week, FR02 and FR03 will be able to be implemented together. 

    As FR04 concerns filtering - it will be necessary to research methods of "fuzzy" searching and associated metrics such as the Levenshtein distance.
  ]

)

#week(
  weekCommencing: "4th March",
  focus: "FR02 & FR03 First Implementation",
  objectives:
  [
    This week will involve the implementations of FR02 and FR03 along with early implementations of FR04. This is in order to provide a sufficient program for presentation at the Mid-Project Demonstration next week. Time allowing, some research into fuzzy searching will take place.
  ],
  tasks:
  [
    1. Implementations of FR02 and FR03.
      - The application now allows users to mark games with a "Status", the current list being #raw("['NONE','BACKLOG','PLAYING','COMPLETED','ABANDONED']"). It is planned in future to allow users to customise the available list of statuses.
    2. Basic Sorting and Filtering functionality (FR04).
      - Users can now filter and sort through the list of available games. However, at the moment users cannot sort by status and name at the same time. Filtering by name also only returns exact matches.
    3. UI Update
      - The UI of the application has been enhanced to provide a better User Experience. The UI is still planned to change drastically before final submission.

    Some internal refactoring of the programs structure also took place this week.
  ],
  challenges:
  [
    While there were no direct challenges this week, it is becoming increasingly clear that some significant changes will need to be made to the underlying code of the application in order to provide a satisfying final product. I am planning to perform any major code changes over the Easter Vacation on a different branch of the Git Repository.
  ],
  plans:
  [
    Next week, as the Mid-Project Demonstration will be taking place on the Friday, I plan to produce some slides and supplementary material. Further, I expect to start improving on FR04, adding fuzzy searching and more ways to filter the library.
  ]
)


#week(
  weekCommencing: "11th March",
  focus: "Mid-Project Demo",
  objectives:
  [
    This week will involve doing the mid-project demonstration and the preparation of some slides. I will also add icons to the games, as this is an important step to improve the presentation of the application.
  ],
  tasks:[
    1. Produced slides for mid-project demonstration
    2. Added icons to the application
    3. Completed the mid-project demonstration
      - Good feedback on description of project and the technical issues & technologies used.
  ],
  challenges:[
    - Average amount of technical work completed in the time available so far - pace of development needs to increase.
  ],
  plans:[],
)

#week(
  weekCommencing: "18th March",
  focus: "Continued development",
  objectives:
  [
    The main objectives of this week are to continue development. This will involve the enhancement of the UI, the implementation of a proper database and looking into the API.
  ],
  tasks:
  [
    1. Cleaned up code, removing unused imports, functions and general refactoring where necessary. This significantly decreased the build time of the application.
  ],
  challenges:
  [
    I have discovered some issues with the performance of the program - notably the complete slowdown of UI when very high resolution icons are used. This will be investigated over Easter.
  ],
  plans:
  [
    The plans for Easter include further implementation of the Functional Requirements, including setting up a proper relational database, and implementing the API.
  ]
)

#[
  #set heading(numbering: none)
  #heading(level: 1)[Easter Vacation: 23rd March - 15th April]

  // Concurrency with API.
  == Completed Tasks

  1. Games now use a relational database to store attributes such as their Genres, Platforms, Developers and Publishers.
    - This uses an "attribute" system, which uses the generic programming principle in order to promote reusable code and decrease repetition.
  2. Improved performance for Game Icons by using the QImage class over the QIcon class, to scale the images down.
  3. Improved the look of the Game Details pane, using Read-Only Line Edits instead of Labels.
  4. Implemented the use of an API to automatically fetch game name, description and attributes. This uses the public Steam API which does not require any api keys.
    - This API is written in python, which is compiled into an executable and then built alongside the main program. This also provides a command-line tool to interface with the API, which is used by the main program.
  5. Began work on the Final Report.

  == Plans for coming weeks
  
  In the final three weeks of the project, I plan to implement CI Testing (some testing is already present in the program) and perform minor enhancements based on feedback from some testers. However, as the end of the project is quickly approaching, there will be a distinct focus on the production of the final report.
]
#pagebreak(weak:true)

#week(
  weekCommencing: "15th April"
)

#week(
  weekCommencing: "22nd April"
)

#week(
  weekCommencing: "29th April",
  focus: "Submission & Final Demo Prep",
  additional: 
  [
    Project Report and Technical Work is due to be submitted on: #datetime(year: 2024, month: 05, day: 03).display().

    The Final Demonstration will take place between #datetime(year: 2024, month: 05, day: 13).display() and #datetime(year: 2024, month: 05, day: 31).display().
  ]
)