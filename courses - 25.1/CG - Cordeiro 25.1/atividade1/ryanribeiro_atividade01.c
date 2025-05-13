// Aluno: Ryan Araujo Ribeiro
// Disciplina: Computacao Grafica

#include <stdio.h>
#include <stdlib.h>

FILE *fpin, *fpoutR, *fpoutG, *fpoutB;
int **imagemR, **imagemG, **imagemB, ncol, nlin, quantizacao;
char nome_saida[256];
char nome_base[256];

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(void);
void ler_imagem(void);
void gravar_cabecalho(void);
void gravar_imagemR(void);
void gravar_imagemG(void);
void gravar_imagemB(void);
void fechar_arquivos(void);
void gerar_cinza_simples(char *nome_saida);
void gerar_cinza_ponderado(char *nome_saida);
void gerar_negativo(char *nome_saida);
void extrair_nome_base(char *caminho);
void gerar_nome_arquivo(char* sufixo, char* extensao);
void processar_imagens(void);
void liberar_memoria(void);

void abrir_arquivos(int argc, char *argv[]) {
     if (argc  <=1) {
	    printf("Modo correto de uso: <prog> <imagemIn>\n\n");
	    exit(0);
     }
     if ((fpin=fopen(argv[1],"r"))==NULL) {
	    printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[1]);
	    exit(1);
     }
    if ((fpoutR=fopen("ImagemR.ppm","w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida R\n" );
        exit(1);
     }
     if ((fpoutG=fopen("ImagemG.ppm","w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida G\n");
        exit(1);
     }
     if ((fpoutB=fopen("ImagemB.ppm","w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida B\n");
        exit(1);
     }

} // Fim: abrir_arquivos

void ler_imagem(void) {
  int cont, col, lin;
  imagemR= (int **)malloc((nlin)*sizeof(int *));
  if (imagemR == NULL) {
    printf("Falha na alocacao de memoria para imagemR\n");
    exit(1);
  }
  imagemG= (int **)malloc((nlin)*sizeof(int *));
  if (imagemG == NULL) {
    printf("Falha na alocacao de memoria para imagemG\n");
    exit(1);
  }

  imagemB= (int **)malloc((nlin)*sizeof(int *));
  if (imagemB == NULL) {
    printf("Falha na alocacao de memoria para imagemB\n");
    exit(1);
  }

  for (cont=0;cont<nlin;cont++) {
    imagemR[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemG[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemG[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemB[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemB[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      if (fscanf(fpin,"%d ",&imagemR[lin][col]) != 1) {
        printf("Erro na leitura do canal R[%d][%d]. Arquivo pode estar corrompido.\n", lin, col);
        exit(1);
      }
      if (fscanf(fpin,"%d ",&imagemG[lin][col]) != 1) {
        printf("Erro na leitura do canal G[%d][%d]. Arquivo pode estar corrompido.\n", lin, col);
        exit(1);
      }
      if (fscanf(fpin,"%d ",&imagemB[lin][col]) != 1) {
        printf("Erro na leitura do canal B[%d][%d]. Arquivo pode estar corrompido.\n", lin, col);
        exit(1);
      }
    }
  }
} // Fim: ler_imagem

void ler_cabecalho(void) {
     char controle[4];
     if (fscanf(fpin,"%3s", controle) != 1) {
        printf("Erro ao ler o formato do arquivo. Arquivo pode estar corrompido.\n");
        exit(1);
     }
     if (fscanf(fpin, "%d %d",&ncol,&nlin) != 2) {
        printf("Erro ao ler as dimensões da imagem. Arquivo pode estar corrompido.\n");
        exit(1);
     }
     if (fscanf(fpin,"%d",&quantizacao) != 1) {
        printf("Erro ao ler o valor de quantização. Arquivo pode estar corrompido.\n");
        exit(1);
     }
} // Fim: ler_cabecalho

void fechar_arquivos(void) {
  fclose(fpin);
  fclose(fpoutR);
  fclose(fpoutG);
  fclose(fpoutB);
} // Fim: fechar_arquivos

void gravar_imagemR(void) {
  int lin, col;
  fprintf(fpoutR,"P3\n");
  fprintf(fpoutR,"%d %d\n",ncol,nlin);
  fprintf(fpoutR,"%d\n",quantizacao);
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fprintf(fpoutR,"%d ",imagemR[lin][col]);
      fprintf(fpoutR,"0 ");
      fprintf(fpoutR,"0 ");
    }
    fprintf(fpoutR,"\n");
  }
} //gravar_imagemR

void gravar_imagemG(void) {
  int lin, col;
  fprintf(fpoutG,"P3\n");
  fprintf(fpoutG,"%d %d\n",ncol,nlin);
  fprintf(fpoutG,"%d\n",quantizacao);
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fprintf(fpoutG,"0 ");
      fprintf(fpoutG,"%d ",imagemG[lin][col]);
      fprintf(fpoutG,"0 ");
    }
    fprintf(fpoutG,"\n");
  }
} //gravar_imagemG

void gravar_imagemB(void) {
  int lin, col;
  fprintf(fpoutB,"P3\n");
  fprintf(fpoutB,"%d %d\n",ncol,nlin);
  fprintf(fpoutB,"%d\n",quantizacao);
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fprintf(fpoutB,"0 ");
      fprintf(fpoutB,"0 ");
      fprintf(fpoutB,"%d ",imagemB[lin][col]);
    }
    fprintf(fpoutB,"\n");
  }
} //gravar_imagemB

void gerar_cinza_simples(char *nome_saida) {
  FILE *fpout;
  int lin, col, valor_cinza;
  if ((fpout=fopen(nome_saida,"w"))==NULL) {
    printf("Nao foi possivel abrir arquivo de saida %s\n", nome_saida);
    exit(1);
  }
  fprintf(fpout,"P2\n");  // P2 para PGM (escala de cinza)
  fprintf(fpout,"%d %d\n",ncol,nlin);
  fprintf(fpout,"%d\n",quantizacao);
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      valor_cinza = (imagemR[lin][col] + imagemG[lin][col] + imagemB[lin][col]) / 3;
      fprintf(fpout,"%d ",valor_cinza);
    }
    fprintf(fpout,"\n");
  }
  fclose(fpout);
} //gerar_cinza_simples

void gerar_cinza_ponderado(char *nome_saida) {
  FILE *fpout;
  int lin, col;
  float valor_cinza;
  
  if ((fpout=fopen(nome_saida,"w"))==NULL) {
    printf("Nao foi possivel abrir arquivo de saida %s\n", nome_saida);
    exit(1);
  }
  
  fprintf(fpout,"P2\n");  // P2 para PGM (escala de cinza)
  fprintf(fpout,"%d %d\n",ncol,nlin);
  fprintf(fpout,"%d\n",quantizacao);
  
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      valor_cinza = 0.299*imagemR[lin][col] + 0.587*imagemG[lin][col] + 0.114*imagemB[lin][col];
      fprintf(fpout,"%d ", (int)valor_cinza);
    }
    fprintf(fpout,"\n");
  }
  fclose(fpout);
} //gerar_cinza_ponderado

void gerar_negativo(char *nome_saida) {
  FILE *fpout;
  int lin, col;
  
  if ((fpout=fopen(nome_saida,"w"))==NULL) {
    printf("Nao foi possivel abrir arquivo de saida %s\n", nome_saida);
    exit(1);
  }
  
  fprintf(fpout,"P3\n");  // P3 para PPM (colorido)
  fprintf(fpout,"%d %d\n",ncol,nlin);
  fprintf(fpout,"%d\n",quantizacao);
  
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fprintf(fpout,"%d ", quantizacao - imagemR[lin][col]);
      fprintf(fpout,"%d ", quantizacao - imagemG[lin][col]);
      fprintf(fpout,"%d ", quantizacao - imagemB[lin][col]);
    }
    fprintf(fpout,"\n");
  }
  fclose(fpout);
} //gerar_negativo

void extrair_nome_base(char *caminho) {
    int i, j, ultimo_separador = -1, ultimo_ponto = -1;
    
    // Encontrar a última ocorrência de '\\' ou '/'
    for (i = 0; caminho[i] != '\0'; i++) {
        if (caminho[i] == '\\' || caminho[i] == '/') {
            ultimo_separador = i;
        }
        if (caminho[i] == '.') {
            ultimo_ponto = i;
        }
    }
    
    // Copiar da posição após o separador até o ponto (ou fim)
    j = 0;
    for (i = ultimo_separador + 1; i < ultimo_ponto && caminho[i] != '\0'; i++) {
        nome_base[j++] = caminho[i];
    }
    nome_base[j] = '\0';
} // extrair_nome_base

void gerar_nome_arquivo(char* sufixo, char* extensao) {
  int i = 0;
  
  // Limpa o buffer de saída
  nome_saida[0] = '\0';
  
  // Copia o nome base
  while (nome_base[i] != '\0') {
    nome_saida[i] = nome_base[i];
    i++;
  }
  
  // Adiciona o sufixo e a extensao
  nome_saida[i++] = '_';
  nome_saida[i++] = sufixo[0];
  nome_saida[i++] = '.';
  
  // Adiciona a extensao
  int j = 0;
  while (extensao[j] != '\0') {
    nome_saida[i++] = extensao[j++];
  }
  
  nome_saida[i] = '\0';
}

void processar_imagens() {
  // Versão 1: Tons de cinza (media simples)
  gerar_nome_arquivo("1", "pgm");
  gerar_cinza_simples(nome_saida);
  
  // Versão 2: Tons de cinza (media ponderada)
  gerar_nome_arquivo("2", "pgm");
  gerar_cinza_ponderado(nome_saida);
  
  // Versão 3: Negativo (inversão de cores)
  gerar_nome_arquivo("3", "ppm");
  gerar_negativo(nome_saida);
} // processar_imagens

void liberar_memoria(void) {
  int i;
  
  // Liberar cada linha das matrizes
  if (imagemR != NULL) {
    for (i = 0; i < nlin; i++) {
      free(imagemR[i]);
    }
  }
  if (imagemG != NULL) {
    for (i = 0; i < nlin; i++) {
      if (imagemG[i] != NULL) {
        free(imagemG[i]);
      }
    }
  }
  if (imagemB != NULL) {
    for (i = 0; i < nlin; i++) {
      if (imagemB[i] != NULL) {
        free(imagemB[i]);
      }
    }
    // Liberar os arrays de ponteiros
    free(imagemR);
    free(imagemB);
    free(imagemG);
  }
} // liberar_memoria



int main(int argc, char *argv[]) {
  abrir_arquivos(argc,argv);
  ler_cabecalho();
  ler_imagem();
  gravar_imagemR();
  gravar_imagemG();
  gravar_imagemB();
  
  // Extrai o nome base do arquivo de entrada
  extrair_nome_base(argv[1]);
  
  // Gera as três versões solicitadas
  processar_imagens();
  
 
  fechar_arquivos();
  liberar_memoria();
  return 0;
}
