## *DICT - QuickStart*

Type safe wrapper do PIX refeito em Reason nativo!

```reason
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
```

__PS: Isso é só um demo, não um exemplo de como rodar em produção__

## Todo
- [ ] SSL
- [x] Test suite
- [x] Type safety
- [x] POST /entries
- [ ] GET /entries
- [ ] POST /entries/{Key}/delete

## Problemas

Bem, você não vai conseguir rodar na sua máquina pq o teste só funciona se vc estiver dentro da rede do ISPB. Mas você pode dar uma lida no código e rodar os testes. O código Java foi deixado do lado para fins de comparação.

## Requisitos

1. node.js
  a. https://github.com/Schniz/fnm
1. esy 
  a. `npm i -g esy`

## Executando

Setup
```
esy
```

Rodando
```
esy x PixDictQuickstartApp.exe
```

## Testes
```
esy x TestPixDictQuickstart.exe
```

<small>Made with 🧐 by Astrocoders</small>
