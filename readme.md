## *DICT - QuickStart*

Type safe wrapper do PIX (Pagamentos Instantâneos do BACEN) refeito em Reason que compila para código nativo!

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

Bem, você não vai conseguir rodar em sua máquina porque o ambiente de testes só funciona dentro da rede do ISPB. Mas você pode dar uma lida no código e rodar os testes. O código Java foi deixado em nosso repo para fins de comparação.

Veja como é facil e seguro a utilização de uma linguagem como ReasonML.

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

<small>Made with 🧐 by [Astrocoders](https://astrocoders.com)</small>
