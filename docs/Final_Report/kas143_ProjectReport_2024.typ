#import "template.typ": *

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
    

    = Declaration of originality

    I confirm that:
    - This submission is my own work, except where clearly indicated.
    - I understand that there are severe penalties for Unacceptable Academic Practice, which can lead to loss of marks or even the withholding of a degree.
    - I have read the regulations on Unacceptable Academic Practice from the University's Academic Registry (AR) and the relevant sections of the current Student Handbook of the Department of Computer Science.
    - In submitting this work I understand and agree to abide by the University's regulations governing these issues.

    / Name: Kal Sandbrook
    / Date: 9th April 2024

    = Consent to share this work

    By including my name below, I hereby agree to this project's report and technical work being made available to other students and academic staff of the Aberystwyth Computer Science Department.

    / Name: Kal Sandbrook
    / Date: 9th April 2024

    = Acknowledgements
  ]

  #page[
    = Abstract
  ]

  #page[
    #outline(indent: true)
    #outline(title: [List of Figures],target: figure)
  ]
]

= Background & Objectives
== Background

== Analysis

== Process

= Design

= Implementation

= Testing

= Evaluation

#bibliography("bibliography.yml", style: "ieee", full: true)

#heading(numbering: none)[Appendices]