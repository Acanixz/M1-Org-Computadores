#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "calculos.h"

using namespace std;

// Armazena informações geradas pelo binary dump
struct LinhaASM{
    // Instrução completa (32 bits)
    string instrucao;

    // Substrings da instrução completa
    string opcode;
    string rd;
    string funct3;
    string rs1;
    string rs2;
    string funct7;

    // Variaveis informativas
    string tipoInstrucao;
};

// Uma organização, utilizado para gerar estatisticas com um vetor de LinhaASM
struct Organizacao{
    float clock;
    map<string, float> quantCiclos; // Quantos ciclos leva cada instrução?

    Organizacao() {
        quantCiclos["U"] = 1.f;
        quantCiclos["J"] = 1.f;
        quantCiclos["B"] = 1.f;
        quantCiclos["I_ar"] = 1.f; // Quant. Ciclos p/ instrução Imm. Aritmetico
        quantCiclos["I_lo"] = 1.f; // Quant. Ciclos p/ instrução Imm. Load
        quantCiclos["R"] = 1.f;
        quantCiclos["S"] = 1.f;
    }
};

// Resultados de desempenho da organização com um binary dump
struct Resultados{
    float CiclosTotais; // Ciclos totais gastos
    float CPI; // Ciclos por instrução
    float Texec; // Tempo de execução (Quant. instrucoes * CPI * Clock)
};

// Abre o arquivo, redundante, mas quem sabe
// ganha um proposito melhor depois
bool abrirArquivo(ifstream &saida, string caminho){
    saida.open(caminho);
    if (saida.is_open()){
        return true;
    }
    cout << "Nao foi possivel abrir o arquivo: " << caminho << endl;
    return false;
}

string lerOpcode(string opcode){
    if (opcode == "0110111" || opcode == "0010111")
        return "U";
    
    if (opcode == "1101111")
        return "J";
    
    if (opcode == "1100011")
        return "B";
    
    if (opcode == "1100111" || opcode == "0000011" || opcode == "0010011")
        return "I";
    
    if (opcode == "0110011")
        return "R";
    
    if (opcode == "0100011")
        return "S";
    
    cout << "(aviso) opcode desconhecido: " << opcode << endl;
    return "?";
}

// Recebe um ifstream para ler e gera um vetor
// cada indice do vetor representa uma instrução de 32 bits
vector<LinhaASM> lerArquivo(ifstream &arquivo){
    vector<LinhaASM> instrucoes;

    if (!arquivo.is_open()){
        throw std::runtime_error("Abra o arquivo antes de tentar ler!");
    }
    
    int i = 0;
    while (arquivo.good()){
        i++;
        LinhaASM linhaAtual;
        arquivo >> linhaAtual.instrucao;

        if (linhaAtual.instrucao.size() != 32){
            if (arquivo.good()){
                // alguma linha não está certa
                throw std::runtime_error("Nao foi possivel ler a linha " + to_string(i) + ", verifique o arquivo.");
            } else {
                // newline final, só ignorar
                continue;
            }
        }
        
        // obs: a ordem dos numeros é o inverso do site
        // https://jemu.oscc.cc/ADD
        // (site vai da direita pra esquerda, aqui é esq. pra dir.)
        linhaAtual.opcode = linhaAtual.instrucao.substr(25, 7);
        linhaAtual.rd = linhaAtual.instrucao.substr(20, 5);
        linhaAtual.funct3 = linhaAtual.instrucao.substr(17, 3);
        linhaAtual.rs1 = linhaAtual.instrucao.substr(12, 5);
        linhaAtual.rs2 = linhaAtual.instrucao.substr(7, 5);
        linhaAtual.funct7 = linhaAtual.instrucao.substr(0, 7);

        linhaAtual.tipoInstrucao = lerOpcode(linhaAtual.opcode);
        // se tudo deu certo, pode colocar no array
        instrucoes.push_back(linhaAtual);
    }
    

    return instrucoes;
}

// Retorna uma organizacao conforme
// entrada do usuário
Organizacao criarOrganizacao(string nome){
    cout << "----------------------\n ORGANIZACAO " << nome << endl;
    Organizacao resultado;
    cout << "Forneca o clock da organizacao " << nome << ": ";
    cin >> resultado.clock;

    for (auto const& [key, value]: resultado.quantCiclos){
        cout << "Forneca a quantidade de ciclos para instrucoes tipo " << key << ": ";
        cin >> resultado.quantCiclos[key];
    }
    cout << "----------------------" << endl << endl;
    return resultado;
}

Resultados calcularResultados(vector<LinhaASM> programa, Organizacao organizacao){
    Resultados resultado;

    std::map<std::string, float> somaCiclos = {
        {"U", 0.f},
        {"J", 0.f},
        {"B", 0.f},
        {"I_ar", 0.f},
        {"I_lo", 0.f},
        {"R", 0.f},
        {"S", 0.f},
    };
    // TODO: for loop de vector<LinhaASM> p/ somar valores
    return resultado;
}

int main(){
    // Temporariamente comentado
    //Organizacao orgA = criarOrganizacao("A");
    //Organizacao orgB = criarOrganizacao("B");

    ifstream progA;
    abrirArquivo(progA, "binary_dump");
    vector<LinhaASM> instrucoes = lerArquivo(progA);

    for (int i = 0; i < instrucoes.size(); i++){
        cout << "INSTRUCAO " << i+1 << " completa: " << instrucoes[i].instrucao << endl;
        cout << "TIPO DE INSTRUCAO: " << instrucoes[i].tipoInstrucao << endl;
        cout << "INSTRUCAO " << i+1 << " separada: " 
        << instrucoes[i].funct7 << " "
        << instrucoes[i].rs2  << " "
        << instrucoes[i].rs1  << " "
        << instrucoes[i].funct3  << " "
        << instrucoes[i].rd  << " "
        << instrucoes[i].opcode
        << endl << endl;
    }

    return 0;
}