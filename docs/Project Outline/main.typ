#import("template.typ"): *

#show: doc.with(
  status: "RELEASE",
  version: "v1.0",
  title: "CS39440: Project Outline",
  subtitle: "Video Game Backlog Application",
  authors: ((name: "Kal Sandbrook", email: "kas143@aber.ac.uk"),),
  supervisors: ((name: "Dr. Edore Akpokodje", email: "eta@aber.ac.uk"),),
  reference: "kas143-ProjectOutline",
)

= Project description <desc>

// A few paragraphs on the project.

This project aims to develop an application which helps users manage their video
game collections in an effective manner. The key goal is provide users with a
platform to curate and view their games, offering features such as: backlog
management, progress tracking and powerful sorting and filtering options.

Users will have the ability to mark a game with various states (such as "abanadoned", "completed"
or "playing"), allowing for easy organization and awareness of a users gaming
endeavours. Additionally, a user will be able to sort and filter games by
information like release date, genre and platform. A tagging system will also be
implemented to further aid categorization based on user preferences.

In the initial stages of development, users will manually input their game data
into the application. However, later stages will see an API being integrated to
automatically fetch game information, providing a more seamless experience. #footnote(
  "The application will allow the user to choose which API to use, and will not be limited to a single API.",
) 

As the project progresses, additional features that will be explored include: a
recommendation system that suggests games based on the user's backlog and
completed games; as well as a social sharing feature to allow users to share
information about their games with others.

Regarding the development platform, whilst a final decision has not been made,
the initial intention is to develop a native desktop application. Further
research will be conducted to determine the optimal platform, with the likely
candidates being Python (PyQt @pyqt) or Java (QtJambi @qtjambi).

The goal of the project is to create a user-friendly and feature-rich
application that caters to the needs of gaming enthusiasts, providing a
comprehensive tool to manage and enhance the games that they are playing.

A variation of the Kanban agile methodology will be used to develop this
project, with tasks being visualised on a kanban board.

= Proposed tasks

// Major parts of work:
//   - Investigation into different plaforms (Python, Java, etc.)
//   - Investigation into APIs
//   - Investigation into recommendation algorithms.
//   - Development:
//     - UI Design
//     - Database Design
//     - API Intergration
//     - Testing 
//   - Usage Documentation
//   - Examples of similar software
//     - HLTB
//     - Backloggr

// Any generated outputs that aren't deliverables.

The major tasks that will need to be undertaken are as follows:

- _Research and Evaluation of Development Platforms_
  - Investigation into the suitability of different platforms for development of the
    application. Factors to be taken into account include the features, capabilities
    and support of each language, along with suitability for an object-oriented
    design.
  - This will involve making small test programs on the platforms in question, to
    get a feel for the suitability of a language.
- _Set up of local environment and version control_
  - An environment will need to be configured for development of the project. The
    specifics of this environment will depend on the chosen platform.
  - The project will use a Git repository for its version control. This will either
    use the University provided GitLab @gitlab instance, or the external service
    GitHub. @github

#pagebreak(weak: true)

- *Development*
  1. _Initial Development and Design_
    - Early development will involve building the essential functions of the
      application. A rough list of initial duties will involve: designing the database
      schema, implementing basic CRUD#footnote("Creating, Reading, Updating and Deleting.") functionality,
      designing the User Interface, the ability to manage the backlog and filter
      through it. At this stage, game data will be provided by the user.
  2. _API Integration and Categorisation_
    - This stage of development will involve making use of external APIs to fetch game
      information and adding a tagging system to allow users to further categorise
      their games.
  3. _Additional Features and Testing_
    - The final stage of development will involve the research and development of the
      additional features outlined in @desc, time permitting. This stage will also
      include a focus on testing, to ensure the application is of sufficient quality. #footnote(
        "Testing will also taking place during development, via unit testing and potentially a Continuous Integration system",
      )

- _Project Meetings & Kanban Board_
  - Throughout the project, weekly meetings will take place with the supervisor. The
    agenda for these meetings will be aided by a kanban board showing work that is
    yet to commence, underway or completed. This kanban board will use the GitLab
    Issue Board #footnote(
      [Details can be seen at: #link("https://docs.gitlab.com/ee/user/project/issue_board.html")],
    ) feature or the GitHub Project feature #footnote(
      [Details can be seen at: #link(
          "https://docs.github.com/en/issues/planning-and-tracking-with-projects/learning-about-projects/about-projects",
        )],
    ). This will allow for a good visualisation of "work done" over each week.

- _Demonstrations_
  - There are two demonstrations scheduled for this project. The first after two
    months of development, and the second at the end of development. For the first
    demonstration mid-project, it is planned that the initial development stage
    (detailed above) will be implemented.



= Project deliverables

The project will deliver the following items throughout and at the end of
development:

- _Demonstration Notes_
  - A set of notes that describe what was shown during the first demonstration. This
    will be included in the appendix of the _Final Report_ and a draft will be
    produced beforehand.

- _Working Software Application_
  - A fully functional video game management application capable of managing user
    game collections, including backlog management, progress tracking, sorting,
    filtering, and tagging features. This will be provided in the form of an
    executable file or installer for Windows and potentially Linux.

\
\
\

- *Final Report*
  - This report will discuss the work and acknowledge any 3rd party tools used in
    the project. It will contain various appendices of documentation produced during
    development, including:
    - Platform Investigation Report
    - User Interface Mockups
    - System Design Documentation
      - There will be documentation included that detail the Database Schema, External
        API Integration, Recommendation System and Sharing Feature.
    - There will be a testing and quality assurance document included, showing the
      results of the tests carried out during development.

- _Final Demonstration_
  - This will not produce any documentation, but it is a deliverable that should be
    considered in planning.

#bibliography("bibliography.yml", style: "./ieee-notes.csl", full: true)
