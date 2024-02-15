// #import("template.typ"): *
#import "@local/report-template:1.0.0": *
#import "@preview/tablex:0.0.8": *

#show: doc.with(
  status: "RELEASE",
  version: "v1.0",
  title: "CS39440: Requirements Analysis",
  subtitle: "GamePile",
  authors: ((name: "Kal Sandbrook", email: "kas143@aber.ac.uk"),),
  supervisors: ((name: "Dr. Edore Akpokodje", email: "eta@aber.ac.uk"),),
  reference: "kas143-RequirementsAnalysis",
)

= Introduction

= Functional Requirements

#tablex(
  columns: (.25fr,1.25fr,.5fr,1fr),
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
  [FR01],[#lorem(20)],[Yes],[#lorem(20)],
  [FR02],[#lorem(20)],[Yes],[#lorem(20)],
  [FR03],[#lorem(20)],[Yes],[#lorem(20)],
  [FR04],[#lorem(20)],[Yes],[#lorem(20)],
  [FR05],[#lorem(20)],[Yes],[#lorem(20)],
)

= Non-Functional Requirements