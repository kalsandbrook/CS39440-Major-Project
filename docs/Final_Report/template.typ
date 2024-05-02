#import "@preview/nth:1.0.0": nth
#import "@preview/wordometer:0.1.1": word-count, total-words


#let smallcaps(content) = {
  text(font: "Century Supra C3")[
    #content
  ]
}

#let titlepage(
  title: "Report Template",
  subtitle: none,
  authors: (),
  supervisors: (),
  date: none,
  hasOutline: bool,
  status: none,
  version: none,
  reference: none,
) = {
  page(
    header: smallcaps[Reference:] + raw(reference),
    numbering: none,
  )[
    #align(
      center,
    )[
      #v(1fr)
      // Title & Subtitle
      #text(size: 2em, weight: "bold")[
        #title
      ]
      \
      #smallcaps(subtitle)
       
      #v(.5em)
       
      Department of Computer Science, \
      Aberystwyth University \
       
      #line(length: 50%)
       
      Last updated: *#date.display(nth(date.day()) + " [month repr:long], [year]")*
       
      *#version* - #status
       
      #line(length: 50%)
       
      #v(.5em)
      // Document Information
      #block[
        // Author Information
        *Produced by:* \
        #authors.map((author) =>
        [
           
          #author.name \
          #link("mailto:" + author.email)[#author.email] \
          BSc in _Computer Science - G400 BSc_ \
        ]).join(";")
         
        #v(1em)
         
        // List supervisors, if any.
        #if (supervisors.len() > 0) {
          [
            *Supervised by:* \
            #supervisors.map((supervisor) =>
            [
               
              #supervisor.name \
              #link("mailto:" + supervisor.email)[#supervisor.email] \
              _Lecturer in Computer Science_
            ]).join(";")
          ]
        }
      ]
      #v(1fr)

      #if (hasOutline) {
        
        outline(
          indent: auto
        )
        v(1fr)
      }
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
  reference: none,
  body,
) = {
  show table: set par(justify: false)
  show link: underline
  // Set the document's basic properties.
  set document(author: authors.map(a => a.name), title: title)
  set page(paper: "a4", margin: margin, footer: [
    #subtitle
    #h(1fr)
    #counter(page).display("1 of 1", both: true)
  ], header: emph[
    #title
    #sym.dash.em
    #status, #version
    #h(1fr)
    #authors.map((author) => 
    [
      #author.name
      #let authorEmailArray = author.email.split("@")
      #if (authorEmailArray.at(1).ends-with(".ac.uk")) {
        "("
        link(author.email)[#authorEmailArray.first()]
        ")"
      }
    ]).join(";")
  ])
  set text(font: "Century Supra T3", size: fontsize, lang: "en")
  set heading(numbering: "1.1 -")
   
  show heading: it => {
    it
    v(.25em)
  }
   
  show cite: super
   
  set list(marker: ([•], [⁃]))

  titlepage(
    title: title,
    subtitle: subtitle,
    authors: authors,
    supervisors: supervisors,
    date: date,
    hasOutline: hasOutline,
    status: status,
    version: version,
    reference: reference,
  )
   
  body
}

#let signatureblock() = {
  grid(
    columns: (1fr,1fr),
    [
      / Name\:: Kal Sandbrook
      / Date\:: 9th April 2024
    ],
    [
      #set align(right)
      #image("assets/signature.png",height:2em)
    ]
  )
}



#let appendixNumbering(..nums) = {
  if (nums.pos().len() == 2){
    return numbering("Appendix A -", nums.pos().at(1))
  } else {
    return numbering("1.1", ..nums.pos().slice(2))
  }
}

#let appendix(
  title: [],
  content
) = [
  #heading(level: 2, numbering: appendixNumbering, supplement: "Appendix")[#title] <appendix>

  #[
    #set heading(numbering: none, outlined: false)
    #content
  ]
]

#let wordcountsec(content) = {
      word-count(total => {
      content
      align(right)[
      //#smallcaps[#total.words words]
      ]
    })
  }