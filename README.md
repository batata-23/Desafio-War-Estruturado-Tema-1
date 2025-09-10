# Desafio-War-Estruturado-Tema-1

Este projeto é uma implementação didática, em C, de um núcleo do jogo *War*.
Conteúdo:
- Estruturas para territórios (nome, cor, tropas, vizinhos).
- Módulo de ataque simulando batalhas com dados.
- Módulo de missões e verificação de condição de vitória.
- Uso de malloc/free, ponteiros, modularização e passagem por referência.

## Estrutura do repositório
```
/WarProject
  /src
    main.c
    territorio.c
    territorio.h
    attack.c
    attack.h
    mission.c
    mission.h
  Makefile
  README.md
```

## Como compilar
No diretório do projeto execute:
```
make
```
Isso gera o executável `war`.

## Como usar
Rode `./war`. O programa contém um menu simples para:
- cadastrar territórios (nome, cor, tropas)
- listar territórios
- conectar territórios (criar vizinhança)
- simular ataque entre territórios
- checar missões (ex: controlar continentes)
- exemplos iniciais já disponíveis no programa

## Observações
- Código feito para fins acadêmicos; modular e comentado.
- Use `make clean` para remover o executável.
