open TestFramework;

describe("XML thingy", ({test}) => {
  open PixDictQuickstart;
  (
    test("should render properly to string", ({expect}) => {
      expect.string(
        XML.toString(
          <Api.CreateEntryRequest
            signature="290129"
            name="Joao da Silva"
            taxId="06036695306"
            key_="1929"
            participant="participant"
            branch="12901"
            accountNumber="12903"
            accountType=CACC
            personType=NATURAL_PERSON
          />,
        ),
      ).
        toEqual(
        "<CreateEntryRequest><Signature>290129</Signature><Entry><Key>1929</Key><Account><Participant>participant</Participant><Branch>12901</Branch><AccountNumber>12903</AccountNumber><AccountType>Api.AccountType.CACC</AccountType></Account><Owner><Type>Api.PersonType.NATURAL_PERSON</Type><TaxIdNumber>06036695306</TaxIdNumber><name>Joao da Silva</name></Owner></Entry></CreateEntryRequest>",
      )
    })
  )
});

describe("API.Entry.Create", ({test}) => {
  open PixDictQuickstart;

  test("should parse a success response", ({expect}) => {
    let response = {|
<?xml version="1.0" encoding="UTF-8"?>
<CreateEntryResponse>
  <Signature></Signature>
  <Entry>
    <Key>11122233300</Key>
    <KeyType>CPF</KeyType>
    <Account>
      <Participant>12345678</Participant>
      <Branch>00001</Branch>
      <AccountNumber>0007654321</AccountNumber>
      <AccountType>CACC</AccountType>
    </Account>
    <Owner>
      <Type>NATURAL_PERSON</Type>
      <TaxIdNumber>11122233300</TaxIdNumber>
      <Name>João Silva</Name>
    </Owner>
    <CreationDate>2019-11-18</CreationDate>
    <KeyOwnershipDate>2019-11-18</KeyOwnershipDate>
  </Entry>
</CreateEntryResponse>
    |};

    expect.equal(
      Api.Entry.Create.parseResponse(response),
      {
        keyType: Some( CPF ),
        key_: Some( "11122233300" ),
        account: {
          participant: Some("12345678"),
          branch:Some( "00001" ),
          accountNumber:Some(  "0007654321" ),
          accountType: Some(CACC),
        },
        owner: {
          type_: Some(NATURAL_PERSON),
          taxIdNumber: Some("11122233300"),
          name: Some({|João Silva|} ),
        },
        creationDate: Some("2019-11-18"),
        keyOwnershipDate: Some("2019-11-18"),
      }
    )
  })
});

TestFramework.cli()