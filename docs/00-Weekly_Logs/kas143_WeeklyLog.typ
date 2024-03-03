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
  tasks:
  [
    1. Final Decision on Programming Language
      - It has been decided that C++ will be the programming language used for this project. The Qt UI Toolkit will also be used.
    2. Continuous Integration
  ],
  plans: "ethics proc"
)

#week(
  weekCommencing: "19th February",
  focus: "Initial Development Complications",
  tasks: 
  [
    1. Learning Qt (using Documentation)
    2. Class Diagram
    3. Rewrite of Project Code
  ],
  challenges: "Illness and Qt not compiling on windows bug - address that development is going slower than planned.",
)

#week(
  weekCommencing: "26th February",
  focus: "FR01 and Gaining Momentum",
  objectives:
  [
    This weeks objectives are to complete FR01. Last week and the beginning of this week resulted in a complete change of how the program is structured, so whilst development has been slow (in terms of the completion of Requirements) - it is anticipated that development will speed up significantly going forward.
  ],
  tasks:
  [
    1. Database Schema
    2. Data Persistence
    3. Code Documentation Generation (doxygen)
      - Continuous Integration
  ],

)

#week(
  weekCommencing: "4th March"
)


#week(
  weekCommencing: "11th March",
  focus: "Mid-Project Demo"
)

#week(
  weekCommencing: "18th March"
)

#[
  #set heading(numbering: none)
  #heading(level: 1)[Easter Vacation: 23rd March - 15th April]

  == Additional Notes
  
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