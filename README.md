# itp-avaliacao2-financeirosemanal

* IDENTIFICAÇÃO:
    NOME: Marcelo Augusto Guilherme Cavalcante
    OPÇÃO: Controle de gastos da semana

* DESCRIÇÃO:
    A ideia do programa é ajudar na organização financeira diária, a função dele é registrar as despesas de segunda a domingo em até cinco categorias diferentes, somar tudo e mostrar em qual área gastamos mais de uma forma organizada.

* COMPILAÇÃO E EXECUÇÃO:
    Este projeto foi desenvolvido em linguagem C e está contido integralmente no arquivo `main.c`. Para compilar e executar o código utilizando o compilador GCC no terminal (Linux, macOS ou Windows via WSL/MinGW), utilize os seguintes comandos:

    ```bash
    gcc -std=c11 -Wall -Wextra main.c -o controle_gastos
    ./controle_gastos

* TESTES:
* Caso de Teste 1 (Valores Válidos):
    Entradas: 2 categorias cadastradas.
    "Alimentação" com R$ 20,00 informados em todos os dias.
    "Transporte" iniciando com R$ 1,00 na segunda-feira e sofrendo incremento de R$ 1,00 a cada dia subsequente.

    Resultado Esperado e Obtido: O sistema registrou o total de R$ 140,00 para Alimentação e R$ 28,00 para Transporte, resultando no total semanal de R$ 168,00. A categoria Alimentação foi corretamente identificada como o maior gasto, representando 83.33% do total da semana.

* Caso de Teste 2 Validação de Limites e Tratamento de Erros:
    Limite de Categorias: Tentativa de criar 6 categorias.
    Resultado: O sistema bloqueou a ação, respeitando o limite máximo definido de 5 categorias.

    Validação de String: Envio de entrada vazia no nome da categoria.
    Resultado: O sistema interceptou a ação e exigiu o preenchimento obrigatório do nome.

    Validação Numérica: Tentativa de inserção do valor negativo de R$ -15,00.
    Resultado: Entrada rejeitada imediatamente, exigindo a inserção de um valor positivo ou zero.

    Prevenção de Divisão por Zero: Preenchimento de todos os dias da semana com o valor R$ 0,00.
    Resultado: O sistema operou normalmente sem travamentos, informou a ausência de gastos e exibiu a porcentagem de ocupação como 0.00%.

* VÍDEO:
    https://youtu.be/WKhaDIx84Tk

* REFERÊNCIAS:
    https://bolder-beret-049.notion.site/Introdu-o-s-T-cnicas-de-Programa-o-9fd602a6688140309f459752ec8ee8bd