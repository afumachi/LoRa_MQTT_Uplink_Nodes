//================ RECEBE O PACOTE DA CAMADA FÍSICA ========
void Mac_radio_receive_DL() { 
  // Aqui pode ser adicionado o Sleep Mode

  // Primeiro ciclo
    if ((recebe_comando_nova_radio == 1)){
     
      Serial.println("[RECONFIGURACAO DE RADIO RECEBIDO]");
      confirma_novo_radio_sensor = 2;
        
    }
    else if (recebe_comando_nova_radio == 3){
      //Serial.println("[TESTE ENLACE RECEBIDO]");
      confirma_novo_radio_sensor = 3;
    }
    else if (recebe_comando_nova_radio == 4){
      //Serial.println("[LSS EM ANDAMENTO]");
      confirma_novo_radio_sensor = 4;
    }    
    if (recebe_comando_nova_radio == 5){
      //Serial.println("[LSS - ÚLTIMO PACOTE]");
      confirma_novo_radio_sensor = 5;
    }
    
    Net_radio_receive_DL();

}

//================ ENVIA O PACOTE À CAMADA FÍSICA ========
void Mac_radio_send_UL() {
  // Aqui pode ser adicionado o Sleep Mode

  // confirmação do primeiro ciclo  
  if (confirma_novo_radio_sensor == 1){
    PacoteUL[7] = 1;
    Serial.println("MAC - PacoteUL[7] - CICLO : ");
    Serial.println(confirma_novo_radio_sensor);
    confirma_novo_radio = 0;
  
  }
  else if (confirma_novo_radio_sensor == 2){
    // Confirmação do segundo ciclo para alteração das config. de rádio do Nó Sensor
    PacoteUL[7] = 2;
    Serial.println("MAC - PacoteUL[7] - RECONFIGURA RADIO : ");
    Serial.println(confirma_novo_radio_sensor);
    confirma_novo_radio = 1; // Habilita Nó Sensor a alterar as configurações de Rádio
    
  }
  else if (confirma_novo_radio_sensor == 3){
    //  Confirmação do terceiro ciclo confirmando a alteração das config. de rádio do Nó Sensor
    PacoteUL[7] = 3;
    Serial.println("MAC - PacoteUL[7] - TESTE ENLACE: ");
    //Serial.println(confirma_novo_radio_sensor);
    recebe_comando_nova_radio = 0;
    confirma_novo_radio = 0;
    confirma_novo_radio_sensor = 0;
  }
  else if (confirma_novo_radio_sensor == 4){
    //  Confirmação do terceiro ciclo confirmando a alteração das config. de rádio do Nó Sensor
    PacoteUL[7] = 4;
    Serial.println("MAC - PacoteUL[7] - CICLO SITE SURVEY: ");
    //Serial.println(confirma_novo_radio_sensor);
    recebe_comando_nova_radio = 0;
    confirma_novo_radio = 0;
    confirma_novo_radio_sensor = 0;
  }
  else if (confirma_novo_radio_sensor == 5){
    //  Confirmação do terceiro ciclo confirmando a alteração das config. de rádio do Nó Sensor
    PacoteUL[7] = 5;
    Serial.println("MAC - PacoteUL[7] - ÚLTIMO CICLO SITE SURVEY: ");
    //Serial.println(confirma_novo_radio_sensor);
    recebe_comando_nova_radio = 0;
    confirma_novo_radio = 0;
    confirma_novo_radio_sensor = 5;
      // Zera flag de contagem e variáveis de controle
    controle_ativo          = false;
    millis_inicio_controle  = 0;
    tempo_radio             = 0;

    confirma_novo_radio_base = 10; // AAF 17-09 Nó Sensor em Standy-by

    contadorDL = 0;
    contadorSS = 0;
    contadorUL = 0;
    contador_perda_DL = 0;
  }
  else {
    // Sem necessidade de alteração, ou confirmação de alteração
    PacoteUL[7] = 0;
    recebe_comando_nova_radio = 0;
    confirma_novo_radio = 0;
    confirma_novo_radio_sensor = 0;

  }

  Phy_radio_send_UL();
}
