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

//STACK POINTER STARTA NO TOPO DA MEMORIA RAM E DESCE ATÉ O FINAL
//HEAP POINTER STARTA JUNTO COM VARIAVEIS STATICAS,STRUTURAS,ETC E VAI ATÉ O FINAL
//SP É A LARGURA DO HEAP POINTER
uint32_t Check() {
  uint8_t * HEAPPTR, * STACKPTR;
  STACKPTR = (uint8_t*)malloc(4);  //USA STACKPTR TEMPORIAMENTE
  HEAPPTR  = STACKPTR;             //SALVA O VALOR DO STACKPTR NA VARIAVEL HEAPPTR
  free(STACKPTR);                  //SETA STACK EM ZERO
  STACKPTR = (uint8_t*)(SP);       //SALVA O VALOR PARA STACKPTR
  return STACKPTR - HEAPPTR;       //RETORNA O VALOR DA MEMORIA RAM LIVRE NO MEGA2560
}

//RETORNA O TOTAL DE MEMORIA RAM USADA EM PORCENTAGEM
uint32_t GetPercentage() {
  //DETECTA AUTOMATICAMENTE O TIPO DE MICROCONTROLADOR USADO
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  static float Free = 2048 - Check();
  return Free / 2048 * 100;
#endif
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  static float Free = 8192 - Check();
  return Free / 8192 * 100;
#endif
}
