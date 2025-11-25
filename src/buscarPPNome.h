#ifndef BUSCARPPNOME_H
#define BUSCARPPNOME_H

// ------------------------------------------------------------------
// Cabeçalho para o relatório que busca pessoas pelo primeiro nome.
// Tabela alinhada + uso de cores ANSI.
// ------------------------------------------------------------------

// Função principal do relatório
void buscarPPNome(void);

// Compara strings ignorando maiúsculas/minúsculas
int iguaisIgnoreCase(const char *a, const char *b);

// Extrai o primeiro nome de um nome completo
void primeiroNome(const char *nomeCompleto, char *dest);

#endif
