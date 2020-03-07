open XML;
open Lwt;
open Cohttp_lwt_unix;

let cpf = "06036695306";
let key = "00038166000105";

let baseAddress = "dict-h.pi.rsfn.net.br/dict/api/v1";
let ispb = "12345678";

module AccountType = {
  [@deriving show]
  type t =
    | CACC
    | SVGS
    | SLRY;

  let fromString =
    fun
    | "CACC" => Some(CACC)
    | "SVGS" => Some(SVGS)
    | "SLRY" => Some(SLRY)
    | _ => None;
};

module PersonType = {
  [@deriving show]
  type t =
    | NATURAL_PERSON
    | LEGAL_PERSON;

  let fromString =
    fun
    | "NATURAL_PERSON" => Some(NATURAL_PERSON)
    | "LEGAL_PERSON" => Some(LEGAL_PERSON)
    | _ => None;
};

module KeyType = {
  [@deriving show]
  type t =
    | CPF
    | PHONE
    | EMAIL;

  let fromString =
    fun
    | "CPF" => Some(CPF)
    | "PHONE" => Some(PHONE)
    | "EMAIL" => Some(EMAIL)
    | _ => None;
};

module CreateEntryRequest = {
  let createElement =
      (
        ~signature,
        ~taxId,
        ~name,
        ~key_,
        ~participant,
        ~branch,
        ~accountNumber,
        ~accountType,
        ~personType,
        ~children as _,
        _,
      ) => {
    <Element name="CreateEntryRequest">
      <Element name="Signature"> <Text text=signature /> </Element>
      <Element name="Entry">
        <Element name="Key"> <Text text=key_ /> </Element>
        <Element name="Account">
          <Element name="Participant"> <Text text=participant /> </Element>
          <Element name="Branch"> <Text text=branch /> </Element>
          <Element name="AccountNumber"> <Text text=accountNumber /> </Element>
          <Element name="AccountType">
            <Text text={AccountType.show(accountType)} />
          </Element>
        </Element>
        <Element name="Owner">
          <Element name="Type">
            <Text text={PersonType.show(personType)} />
          </Element>
          <Element name="TaxIdNumber"> <Text text=taxId /> </Element>
          <Element name="name"> <Text text=name /> </Element>
        </Element>
      </Element>
    </Element>;
  };
};

module Entry = {
  let endpoint = baseAddress ++ "/entries";

  [@deriving show]
  type account = {
    participant: option(string),
    branch: option(string),
    accountNumber: option(string),
    accountType: option(AccountType.t),
  };

  [@deriving show]
  type owner = {
    type_: option(PersonType.t),
    taxIdNumber: option(string),
    name: option(string),
  };

  module Create = {
    [@deriving show]
    type t = {
      keyType: option(KeyType.t),
      key_: option(string),
      account,
      owner,
      creationDate: option(string),
      keyOwnershipDate: option(string)
    };

    let parseResponse: string => t =
      rawResponse => {
        open Soup;
        open Base;

        let soup =
          rawResponse
          |> Markup.string
          |> Markup.parse_xml
          |> Markup.signals
          |> from_signals;

        Option.{
          keyType:
            soup
            $ "CreateEntryResponse Entry KeyType"
            |> leaf_text
            >>= KeyType.fromString,
          key_: soup $ "CreateEntryResponse Entry Key" |> leaf_text,
          account: {
            participant:
              soup
              $ "CreateEntryResponse Entry Account Participant"
              |> leaf_text,
            branch:
              soup
              $ "CreateEntryResponse Entry Account Branch"
              |> leaf_text,
            accountNumber:
              soup
              $ "CreateEntryResponse Entry Account AccountNumber"
              |> leaf_text,
            accountType:
              soup
              $ "CreateEntryResponse Entry Account AccountType"
              |> leaf_text
              >>= AccountType.fromString,
          },
          owner: {
            type_:
              soup
              $ "CreateEntryResponse Entry Owner Type"
              |> leaf_text
              >>= PersonType.fromString,
            taxIdNumber:
              soup $ "CreateEntryResponse Entry Owner TaxIdNumber" |> leaf_text,
            name: soup $ "CreateEntryResponse Entry Owner Name" |> leaf_text,
          },
          creationDate: 
              soup $ "CreateEntryResponse Entry CreationDate" |> leaf_text,
          keyOwnershipDate: 
              soup $ "CreateEntryResponse Entry KeyOwnershipDate" |> leaf_text,
        };
      };

    let post = body => {
      let%lwt (response, responseBody) =
        Client.post(
          ~body=Cohttp_lwt.Body.of_string(toString(body)),
          Uri.make(~scheme="https", ~path=endpoint, ()),
        );

      let%lwt data = responseBody |> Cohttp_lwt.Body.to_string;

      Lwt.return(parseResponse(data));
    };
  };
};