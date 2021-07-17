/******************************INFO**********************************/
//AUTOR:JULIO CESAR MATIAS
//DESENVOLVIDO OFICIALMENTE PARA A CONTROLADORA DE VOO JCFLIGHT
//DATA:AGOSTO DE 2019
/********************************************************************/

//STACK POINTER INICIA NO TOPO DA MEMORIA RAM E DESCE ATÉ O FINAL
//HEAP POINTER INICIA JUNTO COM VARIAVEIS STATICAS,STRUTURAS,ETC... E VAI ATÉ O FINAL
//SP É A LARGURA DO HEAP POINTER
uint32_t Check(void) {
  uint8_t *HEAPPTR, *STACKPTR;
  STACKPTR = (uint8_t*)malloc(4);  //USA STACKPTR TEMPORIAMENTE
  HEAPPTR  = STACKPTR;             //SALVA O VALOR DO STACKPTR NA VARIAVEL HEAPPTR
  free(STACKPTR);                  //SETA STACK EM ZERO
  STACKPTR = (uint8_t*)(SP);       //SALVA O VALOR PARA STACKPTR
  return STACKPTR - HEAPPTR;       //RETORNA O VALOR DA MEMORIA RAM LIVRE NO MICROC
}

//RETORNA O TOTAL DE MEMORIA RAM USADA EM PORCENTAGEM
uint32_t GetPercentage(void) {
  //DETECTA AUTOMATICAMENTE O TIPO DE MICROCONTROLADOR USADO
#if defined(__AVR_ATmega328P__)

  static float Free = 2048 - Check();
  return Free / 2048 * 100;

#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

  static float Free = 8192 - Check();
  return Free / 8192 * 100;

#endif
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("MEMORIA RAM LIVRE:");
  Serial.print(Check());
  Serial.print("  ");
  Serial.print("MEMORIA RAM LIVRE EM PORCENTAGEM:");
  Serial.print(GetPercentage());
  Serial.print("%");
  Serial.println();
}
