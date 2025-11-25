# Sistema de Cupom Fiscal - Impressora Elgin

Sistema de Ponto de Venda (PDV) simplificado com integração à impressora fiscal Elgin.

## Descrição do Projeto

Este projeto é um sistema de atendimento de caixa (PDV) que se integra com impressoras fiscais da Elgin, desenvolvido como projeto final do segundo semestre do curso de Engenharia da Computação. O sistema oferece uma interface interativa para operações básicas da impressora, utilizando a biblioteca oficial da Elgin, demonstrando a aplicação prática dos conceitos de programação.

## Objetivos Principais

Desenvolver um programa que simule um sistema de comunicação com impressoras de cupom fiscal da Elgin, aplicando conceitos fundamentais de programação como:
- Funções da biblioteca da impressora Elgin
- Laços de repetição
- Estruturas condicionais
- Funções personalizadas

## Funcionalidades

O sistema oferece um menu interativo com as seguintes operações:

1. Configurar Conexão
2. Abrir Conexão
3. Impressão de Texto
4. Impressão de QR Code
5. Impressão de Código de Barras
6. Impressão de XML SAT
7. Impressão de XML de Cancelamento SAT
8. Abrir Gaveta Elgin
9. Abrir Gaveta
10. Sinal Sonoro
0. Fechar Conexão e Sair

## Funções da Biblioteca Elgin Implementadas pelo professor e editadas pelo grupo

O projeto utiliza as seguintes funções da biblioteca oficial Elgin:

| Função | Descrição |
|--------|-----------|
| `AbreConexaoImpressora()` | Estabelece conexão com a impressora |
| `FechaConexaoImpressora()` | Encerra a conexão com a impressora |
| `ImpressaoTexto()` | Realiza impressão de texto no cupom |
| `Corte()` | Executa o corte do papel |
| `ImpressaoQRCode()` | Imprime códigos QR |
| `ImpressaoCodigoBarras()` | Imprime códigos de barras |
| `AvancaPapel()` | Avança o papel da impressora |
| `AbreGavetaElgin()` | Abre a gaveta de dinheiro (específico Elgin) |
| `AbreGaveta()` | Abre a gaveta de dinheiro (genérico) |
| `SinalSonoro()` | Emite sinal sonoro |
| `ImprimeXMLSAT()` | Imprime XML de venda SAT |
| `ImprimeXMLCancelamentoSAT()` | Imprime XML de cancelamento SAT |

## Estrutura do Sistema

O sistema utiliza:
- **Laços de Repetição**: Para manter o menu em execução até que o usuário encerrar e sair
- **Estruturas Condicionais**: Para executar as diferentes ações baseadas na escolha do usuário
- **Funções Personalizadas**: Para organizar e modularizar o código além das funções da biblioteca

## Como Usar o sistema

1. Execute o programa
2. Escolha a opção desejada no menu principal (1-10, ou 0 para sair)
3. Siga as instruções na tela para cada operação
4. Para encerrar, selecione a opção 0

## Requisitos do Sistema

- Biblioteca oficial Elgin instalada
- Impressora fiscal Elgin configurada
- Sistema compatível com a biblioteca Elgin

## Observações Importantes

- É necessário estabelecer conexão com a impressora antes de realizar qualquer operação
- Certifique-se de fechar a conexão ao finalizar o uso do sistema
- Mantenha a impressora ligada e com papel durante as operações
