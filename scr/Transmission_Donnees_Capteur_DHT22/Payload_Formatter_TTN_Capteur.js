function decodeUplink(input) 
{
  //Fonction de conversion generee par ChatGPT : ASCii to Str
  let asciiString = String.fromCharCode.apply(null, input.bytes);

  let Caractere_1_to_2 = asciiString.substring(0, 2);
  let Caractere_3_to_4 = asciiString.substring(2, 4);
  let temperature = parseFloat(Caractere_1_to_2 + "." + Caractere_3_to_4);

  let Caractere_5_to_6 = asciiString.substring(4, 6);
  let Caractere_7_to_8 = asciiString.substring(6, 8);
  let humidite = parseFloat(Caractere_5_to_6 + "." + Caractere_7_to_8);

  return {
    data: {
      A_Temperature : temperature,
      B_Humidite : humidite
    },
    warnings: [],
    errors: []
  };
}