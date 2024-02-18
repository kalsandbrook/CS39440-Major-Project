// #import("template.typ"): *
#import "@local/report-template:1.0.0": *
#import "@preview/tablex:0.0.8": *

#show: doc.with(
  status: "RELEASE CANDIDATE",
  version: "v0.9",
  title: "CS39440: Requirements Analysis",
  subtitle: "GamePile",
  authors: ((name: "Kal Sandbrook", email: "kas143@aber.ac.uk"),),
  supervisors: ((name: "Dr. Edore Akpokodje", email: "eta@aber.ac.uk"),),
  reference: "kas143-RequirementsAnalysis",
)

= Introduction

This document presents the requirements analysis for the development of a video game collection management application, titled GamePile. This application is produced as part of the assessment for the #smallcaps[CS39440: Major Project] module and aims to provide users with a tool for effectively managing their video game collections.

The document lays out the groundwork for development of this application, dictating the planned scope, objectives and constraints. Functional Requirements map out the different parts of development, whilst Non-Functional Requirements address critical aspects to be considered _throughout_ development.

Adherence to these requirements will produce a high-quality, feature-rich application.

= Functional Requirements

#tablex(
  columns: (.25fr,1.5fr,.5fr,.75fr),
  header-rows: 1,
  repeat-header: true,
  map-cells: cell => {
    if cell.y == 0 {
      strong(cell.content)
    } else if cell.x == 0 {
      emph(cell.content)
    } else {
      cell
    }
  },
  inset: (top: 10pt, bottom: 10pt, rest: 5pt),
  auto-vlines: false,

  hlinex(stroke: 0pt),
  [ID],[Requirement Description],[Mandatory?],[Comments],
  hlinex(stroke: 1.5pt),
  [FR01],
  [
  *Game Management* ---\ Users will be able to add, delete and edit games in the application, and these games will be displayed to the user.
  ],[Yes],[],
  [FR02],
  [
  *Backlog Management* ---\ Users will be able to see and view games that are marked as a part of the backlog.
  ],[Yes],[Could be merged with FR03],
  [FR03],
  [
  *Progress Tracking* ---\ Users can track their progress on a game, marking them as "abandoned", "completed", "playing". 
  ],[Yes],[],
  [FR04],
  [
  *Sorting and Filtering* ---\ Users can sort and filter games using either information about the game itself, or meta-information about the game (e.g. its tags/status within the application itself).
  ],[Yes],[],
  [FR05],
  [
  *Manual Game Entry* ---\ The application will allow users to add games to the system by specifying data themselves.
  ],[Yes],[This will be implemented early in development, to allow for vigorous testing.],
  [FR06],
  [
  *API Integration* ---\ The application will also allow users to add games via the use of an external API, allowing the quick addition of games to the system. If possible, multiple APIs will be available to choose from.
  ],[Yes],[],
  [FR07],
  [
  *Social Sharing* ---\ The application will allow users to export a visual representation of the games they have completed or have on their backlog, to allow this information to be shared with others.
  ],[No],[],
  [FR08],
  [
  *Recommendation System* ---\ The application will suggest games based on the users completed games and backlog, offering personalised suggestions on what games a user may enjoy playing next.
  ],[No],[],
  [FR09],
  [
  *Desktop Application* ---\ The application will be developed as a native desktop application. At the end of development, there will be available builds for the Windows and Linux operating systems.
  ],[Yes],[]
  // [FR10],
  // [
  // *Game Management* - 
  // ],[Yes],[],
)

= Non-Functional Requirements

#tablex(
  columns: (1fr,5fr),
  header-rows: 1,
  repeat-header: true,
  map-cells: cell => {
    if cell.y == 0 {
      strong(cell.content)
    } else if cell.x == 0 {
      emph(cell.content)
    } else {
      cell
    }
  },
  inset: (top: 10pt, bottom: 10pt, rest: 5pt),
  auto-vlines: false,

  hlinex(stroke: 0pt),
  [ID],[Requirement Description],
  hlinex(stroke: 1.5pt),
  [NFR01],[
    *Usability* ---\ The application should have an intuitive, easy to understand interface that is able to navigated by users with limited technical knowledge. 
  ],
  [NFR02],[
    *Performance* ---\ The application should respond quickly to user interaction, and load game data efficiently - especially when considering the large volume of data the application could be dealing with.
  ],
  [NFR03],[
    *Reliability* ---\ The system should make sure to store data in a robust format, with measures in place to tackle potential data loss or corruption.
  ],
  [NFR04],[
    *Compatibility* ---\ The application should be compatible with the Windows and Linux operating systems.
  ],
  [NFR05],[
    *Maintainability* ---\ The codebase should be well-structured and well-documented, to aid in easy understanding of the code and (although not applicable for this project) future updates.
  ],
  [NFR06],[
    *Interoperability* ---\ As the application will be integrating with external APIs, relevant standards and protocols should be adhered to.
  ],
  [NFR07],[
    *Localization* ---\ Although the application will not be translated into other languages at this time, it should be easy for a theoretical translator to localize the application.
  ],
)