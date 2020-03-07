type node = | Text({text: string}) | Container({name: string, children: list(node) })

module Text = {
  let createElement = (~text, ~children as _, _) => {
    Text({text: text})
  }
}

module Element = {
  let createElement = (~name, ~children, _) => {
    Container({ name, children })
  }
}

let rec toString = node => {
  switch(node) {
    | Text({text}) => text 
    | Container({name, children: []}) => 
      "<" ++ name ++ "/>"
    | Container({name, children}) => 
      "<" ++ name ++ ">"
        ++ { children |> List.map(toString) |> List.fold_left((++), "") } ++
      "</" ++ name ++ ">"
  }
}