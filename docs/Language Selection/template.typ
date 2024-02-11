#import "@preview/nth:1.0.0": nth

// STRIPPED DOWN TEMPLATE FOR UNOFFICIAL DOCUMENTS

#let titlepage(
  title: "Report Template",
  subtitle: none,
  authors: (),
  supervisors: (),
  date: none,
  hasOutline: bool,
  status: none,
  version: none,
) = {
  page(
    header: [],
    numbering: none
  )[
    #align(center)[
      #v(1fr)
      // Title & Subtitle
      #heading(
        outlined: false
      )[#title]
      // Document Information

      #smallcaps[#subtitle]

      Department of Computer Science, \
      Aberystwyth University \

      #line(length: 50%)

      Last updated: *#date.display(nth("[day]") + " [month repr:long], [year]")*

      #if(version != none){
          strong(version)
          if(status != none){
            " - " + status
          }
      }
      

      #line(length: 50%)

      #v(.5em)
      #block[
        // Author Information
        *Produced by:* \
        #authors.map((author) =>
          [

            #author.name \
            #link(author.email) \
            //on *Computer Science - G400 BSc* \
          ]
        ).join(";")

        #v(1em)
        *Not an official assignment document.*
        // List supervisors, if any.
        #if(supervisors.len() > 0){
          [
            *Supervised by:* \
            #supervisors.map((supervisor) =>
            [
              
              #supervisor.name \
              #link(supervisor.email) \
              Lecturer in Computer Science
              
            ]
            ).join(";")
          ]
        }
      ]
      #v(1fr)
      
      #if(hasOutline){
        outline()
      }
      #v(1fr)
    ]
  ]
}

#let doc(
  title: "",
  subtitle: none,
  authors: (),
  supervisors: (),
  date: datetime.today(),
  margin: 2.5cm,
  fontsize: 11pt,
  status: none,
  version: none,
  hasOutline: true,
  body,
) = {
  show link: underline
  show table: set par(justify: false)

  // Set the document's basic properties.
  set document(author: authors.map(a => a.name), title: title)
  set page(
    paper: "a4",
    margin: margin,
    numbering: "1 of 1",
    number-align: center + bottom,
    header: emph[
      #title
      #if(version != none){
        sym.dash.em
        status + ", " + version
      }
      #h(1fr)
      #authors.map((author) => 
      [
        #author.name
        #let authorEmailArray = author.email.split("@")
        #if(authorEmailArray.at(1).ends-with(".ac.uk")){
            "("
            link(author.email)[#authorEmailArray.first()]
            ")"
        }
      ]).join(";")
    ],
  )
  set text(size: fontsize, lang: "en")

  titlepage(
    title: title, 
    subtitle: subtitle,
    authors: authors,
    supervisors: supervisors,
    date: date,
    hasOutline: hasOutline,
    status: status,
    version: version
  )
  
  body
}


