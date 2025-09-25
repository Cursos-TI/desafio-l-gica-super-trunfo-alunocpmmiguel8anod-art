#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    char nome_pais[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade; // calculada
} Carta;

/* Calcula densidade demográfica */
void calcula_densidade(Carta *c) {
    c->densidade = (c->area > 0) ? (float)c->populacao / c->area : 0.0;
}

/* Nome legível do atributo */
const char* nome_atributo(int opcao) {
    switch (opcao) {
        case 1: return "População";
        case 2: return "Área (km^2)";
        case 3: return "PIB";
        case 4: return "Pontos turísticos";
        case 5: return "Densidade demográfica";
        default: return "Inválido";
    }
}

/* Pega valor do atributo como float (para cálculos) */
float valor_atributo(const Carta *c, int opcao) {
    switch (opcao) {
        case 1: return (float)c->populacao;
        case 2: return c->area;
        case 3: return c->pib;
        case 4: return (float)c->pontos_turisticos;
        case 5: return c->densidade;
        default: return 0.0;
    }
}

/* Compara dois valores e retorna 1 se carta1 venceu, -1 se carta2 venceu, 0 se empate */
int compara(float v1, float v2, int invertido) {
    if (fabs(v1 - v2) < 1e-6) return 0;
    if (!invertido)
        return (v1 > v2) ? 1 : -1;
    else
        return (v1 < v2) ? 1 : -1;
}

int main(void) {
    /* --- Cartas pré-definidas --- */
    Carta carta1 = {"Brasil", 214000000, 8515767.0, 1900000000000.0, 30, 0.0};
    Carta carta2 = {"Argentina", 46000000, 2780400.0, 640000000000.0, 15, 0.0};

    calcula_densidade(&carta1);
    calcula_densidade(&carta2);

    printf("=== Super Trunfo - Nível Mestre ===\n\n");
    printf("Cartas em jogo:\n");
    printf("1) %s\n2) %s\n\n", carta1.nome_pais, carta2.nome_pais);

    int atributo1, atributo2;

    /* Menu para escolher o primeiro atributo */
    printf("Escolha o PRIMEIRO atributo para comparação:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos turísticos\n5 - Densidade demográfica\nOpção: ");
    scanf("%d", &atributo1);

    switch (atributo1) {
        case 1: case 2: case 3: case 4: case 5:
            printf("\nVocê escolheu: %s\n\n", nome_atributo(atributo1));
            break;
        default:
            printf("\nOpção inválida! Encerrando o jogo.\n");
            return 0;
    }

    /* Menu para o segundo atributo (dinâmico: sem repetir o primeiro) */
    printf("Escolha o SEGUNDO atributo (diferente do primeiro):\n");
    for (int i = 1; i <= 5; i++) {
        if (i != atributo1) {
            printf("%d - %s\n", i, nome_atributo(i));
        }
    }
    printf("Opção: ");
    scanf("%d", &atributo2);

    if (atributo2 == atributo1 || atributo2 < 1 || atributo2 > 5) {
        printf("\nOpção inválida! Encerrando o jogo.\n");
        return 0;
    }

    printf("\nVocê escolheu os atributos: %s e %s\n", nome_atributo(atributo1), nome_atributo(atributo2));

    /* Pega valores */
    float v1a1 = valor_atributo(&carta1, atributo1);
    float v2a1 = valor_atributo(&carta2, atributo1);
    float v1a2 = valor_atributo(&carta1, atributo2);
    float v2a2 = valor_atributo(&carta2, atributo2);

    /* Aplica comparações (regra invertida só para densidade) */
    int res1 = compara(v1a1, v2a1, atributo1 == 5 ? 1 : 0);
    int res2 = compara(v1a2, v2a2, atributo2 == 5 ? 1 : 0);

    /* Soma final */
    float soma1 = v1a1 + v1a2;
    float soma2 = v2a1 + v2a2;

    printf("\n=== Resultado da Comparação ===\n");
    printf("%s:\n  %s = %.2f\n  %s = %.2f\n  Soma = %.2f\n\n",
           carta1.nome_pais, nome_atributo(atributo1), v1a1,
           nome_atributo(atributo2), v1a2, soma1);
    printf("%s:\n  %s = %.2f\n  %s = %.2f\n  Soma = %.2f\n\n",
           carta2.nome_pais, nome_atributo(atributo1), v2a1,
           nome_atributo(atributo2), v2a2, soma2);

    /* Decide vencedor pela soma */
    if (fabs(soma1 - soma2) < 1e-6) {
        printf("Resultado final: Empate!\n");
    } else {
        printf("Resultado final: %s venceu!\n",
               (soma1 > soma2) ? carta1.nome_pais : carta2.nome_pais); // operador ternário
    }

    return 0;
}
