#ifndef CALCULOS_H
#define CALCULOS_H

#include <iostream>
#include <fstream>

using namespace std;

// Calculos feitos a partir da tabela de formulas disponivel no AVA

float gerarDesempenho(float tempoExecucao) {
	return 1.0 / tempoExecucao;
}

// Cout dos dois m�todos de compara��o de desempenho
void responderDesempenho(float resultado) {
	cout << "RESULTADO: " << resultado << endl;
	float porcentagem1 = (resultado - 1) * 100;

	float porcentagem2 = 100 - porcentagem1;
	float porcentagem3 = 100 + porcentagem1;
	if (resultado > 1) {
		cout << "Arquitetura X possui " << porcentagem1 << "% a mais de desempenho do que Arquitetura B" << endl;
		cout << "Enquanto a arquitetura B possui apenas " << porcentagem2 << "% do desempenho da arquitetura A" << endl;
		return;
	}
	if (resultado < 1) {
		cout << "Arquitetura X possui apenas " << porcentagem3 << "% do desempenho da Arquitetura B" << endl;
		cout << "Enquanto a arquitetura B possui " << -porcentagem1 << "% a mais de desempenho do que arquitetura A" << endl;
		return;
	}

	cout << "Arquitetura X e Y possuem o mesmo desempenho para este programa!" << endl;
	return;
}

// Compara��o de desempenho por desempenho
// Formula = desempenhoX / desempenhoY
float compararDesempenhoPorDesempenho(float desempenhoX, float desempenhoY) {
	float resultado = desempenhoX / desempenhoY;
	responderDesempenho(resultado);
	return resultado;
}

// Compara��o de desempenho por tempo de execu��o
// Formula = tempoExecY / tempoExecX
float compararDesempenhoPorTempoExec(float tempoExecucaoX, float tempoExecucaoY) {
	float resultado = tempoExecucaoY / tempoExecucaoX;
	responderDesempenho(resultado);
	return resultado;
}

// Retorna os ciclos da CPU
// Formula = quantInstrucoes * CPI
float gerarCiclosCPU(int quantInstrucoes, float CPI) {
	return quantInstrucoes * CPI;
}

// Tempo de execu��o da CPU por tempo de clock
// Formula = QuantInstrucoes * CPI * TempoClock
// OBS: CiclosCPU = QuantInstrucoes * CPI
float TExecCPUPorTempoClock(int quantInstrucoes, float CPI, float tempoClock) {
	return quantInstrucoes * CPI * tempoClock;
}

// Tempo de execu��o da CPU por frequencia de clock
// Formula = (quantInstrucoes * CPI) / FreqClock
// OBS: CiclosCPU = QuantInstrucoes * CPI
float TExecCPUPorFreqClock(int quantInstrucoes, float CPI, float freqClock) {
	return (quantInstrucoes * CPI) / freqClock;
}

/* Taxa de execu��o das instru��es
* ainda n�o utilizado, ent�o vamos deixar aqui pra caso a M2 precise
* � MUITA FORMULA AAAAA
float taxaExecInstrucoes() {

}
*/

// Ciclos-Por-Instru��o
// Formula = CiclosCPU / quantInstrucoes
// EXPERIMENTAL, TALVEZ N�O ESTEJA CERTO
// (varia��o da formula de ciclosCPU)
float gerarCPI(float ciclosCPU, int quantInstrucoes) {
	return ciclosCPU / quantInstrucoes;
}

/*
* tamb�m ainda n�o utilizado
float TMedioExecucao(){

}
*/

#endif // CALCULOS_H