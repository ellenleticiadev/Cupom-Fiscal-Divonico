#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
//* ======================= Config DLL ======================= */
static HMODULE g_hDll = NULL;

//* Convenção de chamada (Windows): __stdcall */
#ifndef CALLCONV
#  define CALLCONV WINAPI
#endif

//* ======================= Assinaturas da DLL ======================= */
typedef int (CALLCONV *AbreConexaoImpressora_t)(int, const char *, const char *, int);
typedef int (CALLCONV *FechaConexaoImpressora_t)(void);
typedef int (CALLCONV *ImpressaoTexto_t)(const char *, int, int, int);
typedef int (CALLCONV *Corte_t)(int);
typedef int (CALLCONV *ImpressaoQRCode_t)(const char *, int, int);
typedef int (CALLCONV *ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
typedef int (CALLCONV *AvancaPapel_t)(int);
typedef int (CALLCONV *AbreGavetaElgin_t)(int, int, int);
typedef int (CALLCONV *AbreGaveta_t)(int, int, int);
typedef int (CALLCONV *SinalSonoro_t)(int, int, int);
typedef int (CALLCONV *ImprimeXMLSAT_t)(const char *, int);
typedef int (CALLCONV *ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
typedef int (CALLCONV *InicializaImpressora_t)(void);

/* ======================= Ponteiros ======================= */
static AbreConexaoImpressora_t        AbreConexaoImpressora        = NULL;
static FechaConexaoImpressora_t       FechaConexaoImpressora       = NULL;
static ImpressaoTexto_t               ImpressaoTexto               = NULL;
static Corte_t                        Corte                        = NULL;
static ImpressaoQRCode_t              ImpressaoQRCode              = NULL;
static ImpressaoCodigoBarras_t        ImpressaoCodigoBarras        = NULL;
static AvancaPapel_t                  AvancaPapel                  = NULL;
static AbreGavetaElgin_t              AbreGavetaElgin              = NULL;
static AbreGaveta_t                   AbreGaveta                   = NULL;
static SinalSonoro_t                  SinalSonoro                  = NULL;
static ImprimeXMLSAT_t                ImprimeXMLSAT                = NULL;
static ImprimeXMLCancelamentoSAT_t    ImprimeXMLCancelamentoSAT    = NULL;
static InicializaImpressora_t         InicializaImpressora         = NULL;

/* ======================= Configuração ======================= */
static int   g_tipo      = 1;
static char  g_modelo[64] = "i9";
static char  g_conexao[128] = "USB";
static int   g_parametro = 0;
static int   g_conectada = 0;
char texto[100];

/* ======================= Utilidades ======================= */
#define LOAD_FN(h, name)                                                         \
    do {                                                                         \
        name = (name##_t)GetProcAddress((HMODULE)(h), #name);                    \
        if (!(name)) {                                                           \
            fprintf(stderr, "Falha ao resolver símbolo %s (erro=%lu)\n",         \
                    #name, GetLastError());                                      \
            return 0;                                                            \
        }                                                                        \
    } while (0)

static void flush_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* ======================= Funções para manipular a DLL ======================= */
static int carregarFuncoes(void)
{
    g_hDll = LoadLibraryA("E1_Impressora01.dll");
    if (!g_hDll) {
        fprintf(stderr, "Erro ao carregar E1_Impressora01.dll (erro=%lu)\n", GetLastError());
        return 0;
    }

    LOAD_FN(g_hDll, AbreConexaoImpressora);
    LOAD_FN(g_hDll, FechaConexaoImpressora);
    LOAD_FN(g_hDll, ImpressaoTexto);
    LOAD_FN(g_hDll, Corte);
    LOAD_FN(g_hDll, ImpressaoQRCode);
    LOAD_FN(g_hDll, ImpressaoCodigoBarras);
    LOAD_FN(g_hDll, AvancaPapel);
    LOAD_FN(g_hDll, AbreGavetaElgin);
    LOAD_FN(g_hDll, AbreGaveta);
    LOAD_FN(g_hDll, SinalSonoro);
    LOAD_FN(g_hDll, ImprimeXMLSAT);
    LOAD_FN(g_hDll, ImprimeXMLCancelamentoSAT);
    LOAD_FN(g_hDll, InicializaImpressora);

    return 1;
}

static void liberarBiblioteca(void)
{
    if (g_hDll) {
        FreeLibrary(g_hDll);
        g_hDll = NULL;
    }
}

/* ======================= Funções a serem implementadas pelos alunos ======================= */

static int exibirMenu(void)
{
	
	int opcao;
    printf("\n\n============== Menu ===========================\n\n");
        
        printf(" 1 - Configurar Conexão\n");			//Mostrar a opção de Configurar Conexao
        printf(" 2 - Abrir Conexão\n");					//Mostrar a opção de Abrir Conexao
        printf(" 3 - Impressão Texto\n");				//Mostrar a opção de Impressao Texto
        printf(" 4 - Impressão QRCode\n");				//Mostrar a opção de Impressao QRCode
        printf(" 5 - Impressão Cod Barras\n");			//Mostrar a opção de Impressao Cod Barras
        printf(" 6 - Impressão XML SAT\n");				//Mostrar a opção de Impressao XML SAT
        printf(" 7 - Impressão XML Canc SAT\n");		//Mostrar a opção de Impressao XML Canc SAT
        printf(" 8 - Abrir Gaveta Elgin\n");			//Mostrar a opção de Abrir Gaveta Elgin
        printf(" 9 - Abrir Gaveta\n");					//Mostrar a opção de Abrir Gaveta
        printf(" 10 - Sinal Sonoro\n\n");				//Mostrar a opção de Sinal Sonoro
        printf(" 0 - Fechar Conexão e Sair\n");			//mostrar a opção de Fechar Conexao e Sair
        printf("\n==============================================\n\n: ");
        
        scanf("%d", &opcao);							//Recebe a opção escolhida pelo usuário
        return opcao;
}

static void configurarConexao(void)
{
    // TODO: pedir ao usuário tipo, modelo, conexão e parâmetro
    
    system("cls");
	
	//Solicitamos ao usuario as informações de configuração
	printf("\n\n============== Configuração da impressora =====\n\n");
	printf("\n==================================\n\n Digite o tipo de comunicação\n\n 1	USB\n 2	RS232\n 3	TCP/IP\n 4	Bluetooth\n 5	Impressoras acopladas(Android)\n\n: "); //Solicitamos ao usuario o tipo de comunicação
	scanf("%d", &g_tipo);
	printf("\n==================================\n\n Digite o modelo\n\n i7\n i7 Plus\n i8\n i9\n ix\n Fitpos\n BK-T681\n MP-4200 (Para modelos TH e ADV)\n MP-4200 HS\n MK\n MP-2800\n\n: ");//Solicitamos ao usuario o modelo
	scanf("%s", &g_modelo);
	printf("\n==================================\n\n Detalhe de conexão\n\n USB \n RS232		(ex. COM2)\n TCP/IP		(ex. 192.168.0.20)\n Bluetooth	(ex. AA:BB:CC:DD:EE:FF)\n\n: ");//Solicitamos ao usuario o detalhe de conexão
	scanf("%s", &g_conexao);
	printf("\n==================================\n\n Digite o parâmetro (Tipo numérico auxiliar para a conexão com a impressora / Conexao via bluetooh ou USB digite 0.)\n\n: ");//Solicitamos ao usuario o digite o parâmetro
	scanf("%d", &g_parametro);	
	printf("\n Configuração salva!\n");
    
    system("cls");
    
}

static void abrirConexao(void)
{
    // TODO: chamar AbreConexaoImpressora e validar retorno
    
    system("cls");
    printf("\n\n============== Abrir Conexao ==================\n\n");
   if(g_conectada == 1){ // ver se a impressora que esta conectada
   	printf("\n\n A impressora está conectada\n");
	} 
	
	//variavel recebe todos parametros
	int ret = AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);//validar a conexão com a impressora
	if(ret == 0){ //se a conexão esta estabelecida
		g_conectada = 1; //contados vai ser 1 que mostra q esta conectada
		printf("\n\n Conexão estabelecida!\n");
			InicializaImpressora();
	}  else {
		printf("\n\n Falha na conexão da impressora.\n Código de erro: %d\n", ret); //mostrar o erro de conexâo
	}
}   

static void fecharConexao(void)
{
    printf("\n\n Fechando conexão...\n\n");

    if (g_conectada) {
        FechaConexaoImpressora();
        g_conectada = 0;
        printf(" Conexão fechada com sucesso.\n");
    }

    liberarBiblioteca();  // Libera DLL
    exit(0);              // Sai do programa corretamente
}

static void imprimirTexto(void)
{

	system("cls");
	
	 printf("\n\n============== Impressao de texto =============\n\n");

    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	printf(" Digite o texto: ");
    	scanf(" %[^\n]s", texto); // Lê a linha inteira, incluindo espaços ate o enter
    	int ret = ImpressaoTexto(texto, 1, 4, 0);//variavel recebe todos parametros
    	
		AvancaPapel(3);
    	Corte(2);
    	
    	if(ret == 0){ //mostrar se a impressão esta tudo ok
    		printf(" Impressão OK.");
		}else{
			printf(" Erro.\n Retorno: %d\n", ret); //mostrar p redo de impressão
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
}



static void imprimirQRCode(void)
{
	
	system("cls");
	
	 printf("\n\n============== QRCODE =========================\n\n");
	
    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	printf(" Digite o texto: ");
    	scanf(" %[^\n]s", texto);
    	
    	int ret = ImpressaoQRCode(texto, 6,4); //variavel recebe todos parametros
    	
    	AvancaPapel(3);
    	Corte(2);
    	
    	if(ret == 0){
    		printf(" Impressão OK.");
		}else{
			printf(" Erro.\n Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
}

static void imprimirCodigoBarras(void)
{
	
	system("cls");
	
	 printf("\n\n============== Codigo de Barras ===============\n\n");
	
    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	int ret = ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);//variavel recebe todos parametros
    	AvancaPapel(3);
    	Corte(2);
    	
    	
    	if(ret == 0){
    		printf(" Impressão OK.");
		}else{
			printf(" Erro.\n Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
}

static void imprimirXMLSAT(void)
{
	
	// TODO: ler o arquivo ./XMLSAT.xml e enviar via ImprimeXMLSAT
    // incluir AvancaPapel e Corte no final
    
    system("cls");
    
     printf("\n\n============== XMLSAT =========================\n\n");
    
    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	int ret = ImprimeXMLSAT("path=XMLSAT.xml", 0);//variavel recebe todos parametros
    	AvancaPapel(3);
    	Corte(2);
    	
    	
    	if(ret == 0){
    		printf(" Impressão OK.");
		}else{
			printf(" Erro.\n Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
}

static void imprimirXMLCancelamentoSAT(void)
{
    // TODO: ler o arquivo ./CANC_SAT.xml e chamar ImprimeXMLCancelamentoSAT
    // incluir AvancaPapel e Corte no final
    
	/*usar assinatura abaixo:
        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";
        */
        
    system("cls");
        
     printf("\n\n============== CANCELAMENTO XMLSAT ============\n\n"); 
	    
    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	//variavel recebe todos parametros
    	int ret = ImprimeXMLCancelamentoSAT ("path=CANC_SAT.xml", "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZjbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNcSdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQEVd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6CYVFCDtYR9Hi5qgdk31v23w==", 0);
    	AvancaPapel(3);
    	Corte(2);
    	
    	
    	if(ret == 0){
    		printf(" Impressão OK.");
		}else{
			printf(" Erro.\n Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
    //
    
}

static void abrirGavetaElginOpc(void)
{
    // TODO: chamar AbreGavetaElgin(1, 50, 50)
    
	system("cls");
	
	 printf("\n\n============== ABRIR GAVETA ELGIN ============\n\n");
    
	if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	int ret = AbreGaveta (1, 50, 50);//variavel recebe todos parametros
    	
    	if(ret == 0){
    		printf(" Gaveta aberta.");
		}else{
			printf(" Erro ao abrir gaveta. Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
    //
    
}

static void abrirGavetaOpc(void)
{
    // TODO: chamar AbreGaveta(1, 5, 10)
    
    system("cls");
    
     printf("\n\n============== ABRIR GAVETA ==================\n\n");
    
    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    		
    	int ret = AbreGaveta (1, 5, 10);//variavel recebe todos parametros
    	
    	if(ret == 0){
    		printf(" Gaveta aberta.");
		}else{
			printf(" Erro ao abrir gaveta. Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    //
    
}

static void emitirSinalSonoro(void)
{
    // TODO: chamar SinalSonoro(4, 50, 5)
    
    system("cls");
    
     printf("\n\n============== SINAL SONORO ===================\n\n");
    
    if(g_conectada == 1){ //ver se a impressora que esta conectada
    	
    	int ret = SinalSonoro(4, 5, 5); //variavel recebe todos parametros
    	
    	if(ret == 0){
    		printf(" Sinal emitido!");
		}else{
			printf(" Erro ao emitir sinal sonoro.\n Retorno: %d\n", ret);
		}
    	
	}else{
		printf("\n Abra a conexão primeiro.");
	}
    
    //
    
}

/* ======================= Função principal ======================= */


int main(void)
{
	
	setlocale(LC_ALL, "Portuguese");	//Muda a regiao do texto para Português Brasileiro
	
    if (!carregarFuncoes()) {
        return 1;
    }

    int opcao = 0;
    while (1) {
        
        opcao = exibirMenu();
        
        switch(opcao){
        	
        	case 1:		//Configuração de conexão
			configurarConexao();
        	break;
        	
        	case 2:		//Abrir conexão com a impressora
        	abrirConexao();
        	break;
        		
        	case 3:		//Imprimir o texto
        	imprimirTexto();
        	break;
        	
        	case 4:		//Imprimir o QRCode
        	imprimirQRCode();
        	break;
        	
        	case 5:		//Impressão do Cod de Barra
        	imprimirCodigoBarras();
        	break;
        	
        	case 6:		//Impressão do XML SAT
        	imprimirXMLSAT();
        	break;
        	
        	case 7:		//Impressão XML Canc SAT
        	imprimirXMLCancelamentoSAT();
        	break;
        	
        	case 8:		//Configuração para abrir a Gaveta Elgin
        	abrirGavetaElginOpc();
        	break;
        	
        	case 9:		//Configuração para abrir gaveta 
        	abrirGavetaOpc();
        	break;
        	
        	case 10:		//Configuração de Sinal Sonoro
        	emitirSinalSonoro();
        	break;
        	
        	case 0:		//Fecha a conexão e sai
        	fecharConexao();
        	break;
        	
        	default:	// Caso o usuário escolha algum número diferente das opções do menu
        	system("cls");
            printf("\n Opção inválida!\n Digite um numero entre 0 e 10.\n");
            break;
        	
		}
               
    }
    
    
}

