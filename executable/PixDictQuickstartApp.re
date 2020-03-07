let main = () => Lwt_main.run({
  open PixDictQuickstart.Api;
  let%lwt request =
    Entry.Create.post(
      <CreateEntryRequest
        signature="290129"
        name="Joao da Silva"
        taxId="06036695306"
        key_="1929"
        participant="participant"
        branch="12901"
        accountNumber="12903"
        accountType=CACC
        personType=NATURAL_PERSON
      />
    )

  print_endline(Entry.Create.show(request))

  Lwt.return()
})

main()
