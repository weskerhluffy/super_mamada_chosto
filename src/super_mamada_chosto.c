/*
 ============================================================================
 Name        : super_mamada_chosto.c
 Author      : lovehinata
 Version     :
 Copyright   : a veces siento que
 Description : Hello World in C, Ansi-style
 ============================================================================
 XXX: https://www.hackerrank.com/challenges/maximum-cost-queries/problem
 */

#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <stdint.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#define CACA_COMUN_TAM_MAX_LINEA (16*200000)
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO (char[1000] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

#define CACA_COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define CACA_COMUN_IDX_INVALIDO ((natural)CACA_COMUN_VALOR_INVALIDO)

typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;
typedef char byteme;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){sleep(10);abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0;
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

void caca_log_debug_func(const char *format, ...);

void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

void caca_comun_timestamp(char *stime) {
	time_t ltime;
	struct tm result;
	long ms;
#ifndef ONLINE_JUDGE
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	caca_comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}
#ifdef CACA_COMUN_LOG
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef CACA_COMUN_LOG
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%12d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (int i = 0; i < filas_tam; i++) {
		caca_comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		caca_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}

static char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(entero_largo_sin_signo *arreglo,
		entero_largo_sin_signo tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2llu",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#else
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	return NULL;
}
static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}

static char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	return NULL;
}
#endif
void caca_comun_strreplace(char s[], char chr, char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

static int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas,
		int *num_columnas, int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

static inline natural caca_comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

#endif
#endif

#define SUPER_MAMADA_CHOSTO_MAX_NODOS (((natural)1E5)+1)

#if 1

typedef struct puto_cardinal {
	union {
		struct {
			int coordenada_y_puto_cardinal;
			int coordenada_x_puto_cardinal;
		} separados_puto_cardinal;
		entero_largo coordenadas_juntas_puto_cardinal;
	} datos_puto_cardinal;
	void *extra;
} puto_cardinal;

#define coord_x datos_puto_cardinal.separados_puto_cardinal.coordenada_x_puto_cardinal
#define coord_y datos_puto_cardinal.separados_puto_cardinal.coordenada_y_puto_cardinal
#define coord_xy datos_puto_cardinal.coordenadas_juntas_puto_cardinal

static inline short puto_cardinal_compacta_a_corto(puto_cardinal *nodo) {
	int coord_xy_compacta = 0;

	coord_xy_compacta = (nodo->coord_x << 8) | nodo->coord_y;

	return coord_xy_compacta;
}

#define puto_cardinal_a_cadena_buffer_local(puto) puto_cardinal_a_cadena((puto),CACA_COMUN_BUF_STATICO)

#define puto_cardinal_mem_local (&(puto_cardinal){0})

static inline puto_cardinal *puto_cardinal_suma(puto_cardinal *p_res,
		puto_cardinal *p_op1, puto_cardinal *p_op2) {
	p_res->coord_x = p_op1->coord_x + p_op2->coord_x;
	p_res->coord_y = p_op1->coord_y + p_op2->coord_y;
	return p_res;
}

#define puto_cardinal_suma_local(p_op1,p_op2) puto_cardinal_suma(&(puto_cardinal){0},p_op1,p_op2)
#define puto_cardinal_suma_a_op1(p_op1,p_op2) puto_cardinal_suma(p_op1,&(puto_cardinal){.coord_x=p_op1->coord_x,.coord_y=p_op1->coord_y},p_op2)

static inline char *puto_cardinal_a_cadena(puto_cardinal *puto, char *buffer) {
	*buffer = '\0';

	sprintf(buffer, "%d,%d(%llx,%hx)", puto->coord_x, puto->coord_y,
			puto->coord_xy, (short )puto_cardinal_compacta_a_corto(puto));

	return buffer;
}

static inline char *puto_cardinal_arreglo_a_cacadena(puto_cardinal *putos,
		natural putos_tam, char *buffer) {
	*buffer = '\0';
	char *buffer_tmp = buffer;

	for (int i = 0; i < putos_tam; i++) {
		natural scritos = sprintf(buffer_tmp, "%s-",
				puto_cardinal_a_cadena(putos+i, CACA_COMUN_BUF_STATICO));
		buffer_tmp += scritos;

	}

	return buffer;
}

#define puto_cardinal_obten_entero_de_extra(puto) ((int)((natural)(puto)->extra & 0xffffffff))
#define puto_cardinal_pon_entero_en_extra(puto,valor) ((puto)->extra=(void *)(entero_largo_sin_signo)((natural)valor))

#endif

#if 1
typedef struct conjunto_pendejo_nodo conjunto_pendejo_nodo;
typedef struct conjunto_pendejo_ctx conjunto_pendejo_ctx;
typedef int (*conjunto_pendejo_compara_cb)(conjunto_pendejo_ctx *ctx,
		conjunto_pendejo_nodo*, conjunto_pendejo_nodo*);
#define CONJUNTO_PENDEJO_MAX_NODOS SUPER_MAMADA_CHOSTO_MAX_NODOS
struct conjunto_pendejo_ctx {
	conjunto_pendejo_nodo *mapeo_llave_a_nodo_conjunto_pendejo_ctx[CONJUNTO_PENDEJO_MAX_NODOS];
	conjunto_pendejo_compara_cb comparacion_nodos_cb_conjunto_pendejo_ctx;
	natural pesos_rutas_conjunto_pendejo_ctx[CONJUNTO_PENDEJO_MAX_NODOS];
	entero_largo_sin_signo acumulacion_rutas_cnt_conjunto_pendejo_ctx[CONJUNTO_PENDEJO_MAX_NODOS];
	natural peso_actual_conjunto_pendejo_ctx;
	natural peso_anterior_conjunto_pendejo_ctx;
	natural idx_peso_actual_conjunto_pendejo_ctx;
};

struct conjunto_pendejo_nodo {
	tipo_dato llave;
	natural llaves_conjunto_cnt;
	struct conjunto_pendejo_nodo *padre;
};

typedef puto_cardinal conjunto_pendejo_arista;
#define vertice_x coord_x
#define vertice_y coord_y
#define peso extra

static inline conjunto_pendejo_ctx *conjunto_pendejo_init(
		conjunto_pendejo_compara_cb compara_cb) {
	conjunto_pendejo_ctx *ctx = NULL;

	ctx = calloc(1, sizeof(conjunto_pendejo_ctx));
	assert_timeout(ctx);
	ctx->comparacion_nodos_cb_conjunto_pendejo_ctx = compara_cb;

	return ctx;
}

static inline void conjunto_pendejo_fini(conjunto_pendejo_ctx *ctx) {
	free(ctx);
}

static inline conjunto_pendejo_nodo *conjunto_pendejo_crea_conjunto(
		conjunto_pendejo_ctx *ctx, tipo_dato llave) {
	conjunto_pendejo_nodo *nuevo_nodo = NULL;
	nuevo_nodo = calloc(1, sizeof(conjunto_pendejo_nodo));
	assert_timeout(nuevo_nodo);
	nuevo_nodo->llave = llave;
	nuevo_nodo->llaves_conjunto_cnt = 1;
	return nuevo_nodo;
}

static inline void conjunto_pendejo_enlaza(conjunto_pendejo_ctx *ctx,
		conjunto_pendejo_nodo *nodo_x, conjunto_pendejo_nodo *nodo_y) {
	if (ctx->comparacion_nodos_cb_conjunto_pendejo_ctx(ctx, nodo_x, nodo_y)
			>= 0) {
		nodo_y->padre = nodo_x;
	} else {
		nodo_x->padre = nodo_y;
	}
}

static inline void conjunto_pendejo_une(conjunto_pendejo_ctx *ctx,
		conjunto_pendejo_nodo *nodo_x, conjunto_pendejo_nodo *nodo_y) {
	conjunto_pendejo_enlaza(ctx, nodo_x, nodo_y);
}

static inline conjunto_pendejo_nodo *conjunto_pendejo_encuentra_conjunto(
		conjunto_pendejo_ctx *ctx, tipo_dato llave) {

	conjunto_pendejo_nodo *nodo = NULL;

	nodo = ctx->mapeo_llave_a_nodo_conjunto_pendejo_ctx[llave];
	if (!nodo) {
		nodo = ctx->mapeo_llave_a_nodo_conjunto_pendejo_ctx[llave] =
				conjunto_pendejo_crea_conjunto(ctx, llave);
	}

	while (nodo->padre) {
		nodo = nodo->padre;
	}

	return nodo;
}

static inline void conjunto_pendejo_procesa_aristas(conjunto_pendejo_ctx *ctx,
		conjunto_pendejo_arista *aristas_putas, natural aristas_putas_cnt) {
	if (aristas_putas_cnt) {
		ctx->peso_anterior_conjunto_pendejo_ctx = (natural) aristas_putas->peso;
	}
	for (int i = 0; i < aristas_putas_cnt; i++) {
		conjunto_pendejo_nodo *conjunto_x = NULL;
		conjunto_pendejo_nodo *conjunto_y = NULL;
		conjunto_pendejo_arista *arista_act = aristas_putas + i;

		ctx->peso_actual_conjunto_pendejo_ctx = (natural) arista_act->peso;

		conjunto_x = conjunto_pendejo_encuentra_conjunto(ctx,
				arista_act->vertice_x);
		conjunto_y = conjunto_pendejo_encuentra_conjunto(ctx,
				arista_act->vertice_y);

		assert_timeout(conjunto_x->llave != conjunto_y->llave);

		conjunto_pendejo_une(ctx, conjunto_x, conjunto_y);

		ctx->peso_anterior_conjunto_pendejo_ctx =
				ctx->peso_actual_conjunto_pendejo_ctx;
	}
}

#endif

entero_largo_sin_signo llaves_x[SUPER_MAMADA_CHOSTO_MAX_NODOS] = { 0 };
entero_largo_sin_signo llaves_y[SUPER_MAMADA_CHOSTO_MAX_NODOS] = { 0 };

int super_mamada_chosto_compara_aristas_cb(const void *pa, const void *pb) {
	int res = 0;
	puto_cardinal *a = (puto_cardinal*) pa;
	puto_cardinal *b = (puto_cardinal*) pb;

	res = (int) a->extra - (int) b->extra;

	if (!res) {
		res = a->coord_xy - b->coord_xy;
	}
	return res;
}

int super_mamada_chosto_procesa_conjuntos_cb(conjunto_pendejo_ctx *ctx,
		conjunto_pendejo_nodo* nodo_x, conjunto_pendejo_nodo* nodo_y) {
	natural peso_act = ctx->peso_actual_conjunto_pendejo_ctx;
	natural peso_ant = ctx->peso_anterior_conjunto_pendejo_ctx;
	natural idx_peso_act = ctx->idx_peso_actual_conjunto_pendejo_ctx;
	natural llaves_x_cnt = nodo_x->llaves_conjunto_cnt;
	natural llaves_y_cnt = nodo_y->llaves_conjunto_cnt;
	entero_largo_sin_signo peso_rutas_cnt = 0;

	if (peso_act != peso_ant) {
		ctx->idx_peso_actual_conjunto_pendejo_ctx = ++idx_peso_act;
		ctx->acumulacion_rutas_cnt_conjunto_pendejo_ctx[idx_peso_act] =
				ctx->acumulacion_rutas_cnt_conjunto_pendejo_ctx[idx_peso_act - 1];
	}
	ctx->pesos_rutas_conjunto_pendejo_ctx[idx_peso_act] = peso_act;

	ctx->acumulacion_rutas_cnt_conjunto_pendejo_ctx[idx_peso_act] +=
			llaves_x_cnt * llaves_y_cnt;

	if (llaves_x_cnt >= llaves_y_cnt) {
		nodo_x->llaves_conjunto_cnt += llaves_y_cnt;
	} else {
		nodo_y->llaves_conjunto_cnt += llaves_x_cnt;
	}

	caca_log_debug(
			"el nodo %u se fusiono con %u, aora tienen %u, el peso %u de idx %u las rutas %lu",
			nodo_x->llave, nodo_y->llave, llaves_y_cnt+llaves_x_cnt, peso_act,
			idx_peso_act,
			ctx->acumulacion_rutas_cnt_conjunto_pendejo_ctx[idx_peso_act]);

	return llaves_x_cnt - llaves_y_cnt;
}

typedef puto_cardinal intervalo_consulta;
#define inicio_inter coord_x
#define fin_inter coord_y

static inline natural caca_comun_busqueda_binaria_recursiva(natural *arreglo,
		natural arreglo_tam, natural valor, natural idx_inicio,
		natural idx_final) {
	natural idx_encontrado = CACA_COMUN_VALOR_INVALIDO;
	if (idx_inicio == idx_final) {
		if (arreglo[idx_inicio] == valor) {
			idx_encontrado = idx_inicio;
		} else {
			if (idx_inicio && valor < arreglo[idx_inicio]) {
				idx_encontrado = idx_inicio - 1;
			} else {
				if (valor > arreglo[idx_inicio]) {
					idx_encontrado = idx_inicio;
				}
			}
		}
	} else {
		natural intervalo_tam_mitad = (idx_final - idx_inicio) >> 1;
		natural idx_mitad = idx_inicio + intervalo_tam_mitad;
		natural valor_mitad = arreglo[idx_mitad];
		if (valor_mitad == valor) {
			idx_encontrado = idx_mitad;
		} else {
			if (idx_mitad && valor < valor_mitad) {
				if (idx_mitad - 1 >= idx_inicio) {
					idx_encontrado = caca_comun_busqueda_binaria_recursiva(
							arreglo, arreglo_tam, valor, idx_inicio,
							idx_mitad - 1);
				} else {
					idx_encontrado = idx_mitad - 1;
				}
			}
			if (idx_mitad < arreglo_tam - 1 && valor > valor_mitad) {
				if (idx_mitad + 1 <= idx_final) {
					idx_encontrado = caca_comun_busqueda_binaria_recursiva(
							arreglo, arreglo_tam, valor, idx_mitad + 1,
							idx_final);
				} else {
					idx_encontrado = idx_mitad;
				}
			}
		}
	}
	return idx_encontrado;
}

static inline natural caca_comun_busqueda_binaria(natural *arreglo,
		natural arreglo_tam, natural valor) {
	return caca_comun_busqueda_binaria_recursiva(arreglo, arreglo_tam, valor, 0,
			arreglo_tam - 1);
}

static inline void super_mamada_chosto_core(conjunto_pendejo_arista *aristas,
		natural aristas_tam, intervalo_consulta *consultas,
		natural consultas_tam) {
	conjunto_pendejo_ctx *ctx = NULL;
	entero_largo_sin_signo *acumulacion_rutas_cnt = NULL;
	natural *pesos_rutas = NULL;
	qsort(aristas, aristas_tam, sizeof(conjunto_pendejo_arista),
			super_mamada_chosto_compara_aristas_cb);

	ctx = conjunto_pendejo_init(super_mamada_chosto_procesa_conjuntos_cb);
	conjunto_pendejo_procesa_aristas(ctx, aristas, aristas_tam);

	acumulacion_rutas_cnt = ctx->acumulacion_rutas_cnt_conjunto_pendejo_ctx;
	pesos_rutas = ctx->pesos_rutas_conjunto_pendejo_ctx;

	caca_log_debug("los pesos %s",
			caca_comun_arreglo_a_cadena_natural(pesos_rutas, ctx->idx_peso_actual_conjunto_pendejo_ctx+1, CACA_COMUN_BUF_STATICO));
	caca_log_debug("las acum de rutas %s",
			caca_comun_arreglo_a_cadena_entero_largo_sin_signo(acumulacion_rutas_cnt, ctx->idx_peso_actual_conjunto_pendejo_ctx+1, CACA_COMUN_BUF_STATICO));

	for (int i = 0; i < consultas_tam; i++) {
		intervalo_consulta *inter_act = consultas + i;
		puto_cardinal **arreglin = NULL;
		natural idx_acum_ruta_ini = 0;
		natural idx_acum_ruta_fin = 0;
		entero_largo acum_rutas = 0;

		caca_log_debug("puta consulta pesos %u a %u", inter_act->inicio_inter-1,
				inter_act->fin_inter);

		idx_acum_ruta_ini = caca_comun_busqueda_binaria(pesos_rutas,
				aristas_tam, inter_act->inicio_inter - 1);

		caca_log_debug("el idx ini %u", idx_acum_ruta_ini);

		idx_acum_ruta_fin = caca_comun_busqueda_binaria(pesos_rutas,
				aristas_tam, inter_act->fin_inter);

		caca_log_debug("el idx fin %u", idx_acum_ruta_fin);

		if (idx_acum_ruta_fin != CACA_COMUN_VALOR_INVALIDO) {
			acum_rutas = acumulacion_rutas_cnt[idx_acum_ruta_fin];
			caca_log_debug("d inter fin %llu", acum_rutas);
			if (idx_acum_ruta_ini != CACA_COMUN_VALOR_INVALIDO) {
				acum_rutas -= acumulacion_rutas_cnt[idx_acum_ruta_ini];
				caca_log_debug("d inter ini %llu",
						acumulacion_rutas_cnt[idx_acum_ruta_ini]);
			}
		}

		printf("%llu\n", acum_rutas);

	}

	conjunto_pendejo_fini(ctx);
}

conjunto_pendejo_arista aristas[SUPER_MAMADA_CHOSTO_MAX_NODOS] = { 0 };
intervalo_consulta consultas[SUPER_MAMADA_CHOSTO_MAX_NODOS] = { 0 };

static inline void super_mamada_chosto_main() {
	natural aristas_cnt = 0;
	natural consultas_cnt = 0;

	scanf("%u %u\n", &aristas_cnt, &consultas_cnt);
	aristas_cnt--;

	for (int i = 0; i < aristas_cnt; i++) {
		scanf("%u %u %u\n", &aristas[i].vertice_x, &aristas[i].vertice_y,
				(natural *) &aristas[i].peso);
	}
	for (int i = 0; i < consultas_cnt; i++) {
		intervalo_consulta *inter_act = consultas + i;
		scanf("%u %u\n", &inter_act->inicio_inter, &inter_act->fin_inter);
	}

	super_mamada_chosto_core(aristas, aristas_cnt, consultas, consultas_cnt);
}

int main(void) {
	super_mamada_chosto_main();
	return EXIT_SUCCESS;
}
