#include "projeto.h"

int main() {
    printf("\t .--.                      .-.             .-..-. _                                  .---.  .--. .-.\n");
    printf("\t: .--'                     : :             : :: ::_;                                 : .  :: .--': :\n");
    printf("\t: : _  .--. .--.  .--.   .-' : .--. .--.   : :: :.-. .--.   .--.  .--. ,-.,-. .--.   : :: :: `;  : :\n");
    printf("\t: :; :' '_.': ..'' .; ; ' .; :' .; :: ..'  : `' ;: :' .; ; ' .; :' '_.': ,. :`._-.'  : :; :: :__ : :\n");
    printf("\t`.__.'`.__.':_;  `.__,_;`.__.'`.__.':_;     `.,' :_;`.__,_;`._. ;`.__.':_;:_;`.__.'  :___.'`.__.':_;\n");
    printf("\t                                                            .-. :                                   \n");
    printf("\t                                                            `._.'                                   \n\n");
    utilizador();
    return 0;
}


void utilizador(){
    int aux,status;
    Utilizador atual;
    printf("\t\t[1] Login\n");
    printf("\t\t[2] Registar Utilizador\n");
    printf("\t\t[3] Sair\n");
    do{
        scanf("%d", &aux);
    }while (aux!=1 && aux!=2 && aux !=3);
    if (aux==1) {
        status=login(&atual);
        if (status==1) {
            inicia(&atual);
            return;
        }
    }
    else if(aux==2){
        status = registar();
        if (status==1) {
            utilizador();
            return;
        }
    }
}


int registar(){
    Utilizador novo;
    int aux;
    printf("Nome: ");
    scanf(" %[^\n]",novo.nome);
    aux = consultaNome(novo.nome);
    if (aux==1) {
        registar();
        return 0;
    }
    printf("Morada: ");
    scanf(" %[^\n]",novo.morada);
    do {
        printf("Data de nascimento(dd/mm/aaaa): ");
        scanf("%d/%d/%d",&(novo.dia),&(novo.mes),&(novo.ano));
    } while(novo.mes < 1 || novo.mes > 12);
    printf("Telefone: ");
    scanf("%d",&(novo.telefone));
    gravaUtilizador(&novo);
    return 1;
}


void inicia(Utilizador *atual){
    int aux,totalUtili,local,hot=0,pontosIncluidos,totalPontos,p1, p2, p3;
    List listaPopCidades;
    List listaAlfaCidades;
    Travel via;
    Travel via1;
    Travel via2;
    Viagem viagem;
    Viagem viagem1;
    Viagem viagem2;
    Viagem viagemAlfa;
    printf("\t\t[1] Ordenar Locais e Pontos de Interesse\n");
    printf("\t\t[2] Escolher Ponto de Interesse Hot\n");
    printf("\t\t[3] Escolher Outras Preferencias\n");
    printf("\t\t[4] Ordenar Por Popularidade\n");
    printf("\t\t[5] Gerar Viagem\n");
    printf("\t\t[6] Sair\n");
    scanf("%d", &aux);
    if(aux==1){
        system("@cls");
        listaAlfaCidades = NULL;
        viagemAlfa = NULL;
        listaAlfaCidades = ordemAlfa(listaAlfaCidades);
        print_lista(listaAlfaCidades);
        escolhe_cidade_alfa(listaAlfaCidades,viagemAlfa);
        inicia(atual);
        return;
    }
    if (aux==2) {
        system("@cls");
        prefer(atual);
        inicia(atual);
        return;
    }
    if (aux==3) {
        system("@cls");
        if(strcmp(atual->pdi," ")!=0 && strcmp(atual->pdi,"")!=0){
            preferCidade(atual);
            inicia(atual);
            return;
        }
        else{
            printf("ESCOLHA PRIMEIRO UM HOTSPOT\n");
            inicia(atual);
            return;
        }
    }
    if (aux==4) {
        system("@cls");
        listaPopCidades = NULL;
        viagem = NULL;
        listaPopCidades = leficheiro(listaPopCidades);
        print_lista(listaPopCidades);
        escolhe_cidade(listaPopCidades,viagem);
        inicia(atual);
        return;
    }
    if (aux==5) {
        system("@cls");
        if (strcmp(atual->cidade," ")==0 || strcmp(atual->city1," ")==0 || strcmp(atual->city2," ")==0) {
            printf("ESCOLHA UM HOTSPOT, E DUAS OUTRAS CIDADES DE PREFERENCIA\n");
            inicia(atual);
            return;
        }
        else{
            printf("--------------------------------A SUA VIAGEM---------------------------------\n");
            viagem = NULL;
            viagem1 = NULL;
            viagem2 = NULL;
            via = NULL;
            via1 = NULL;
            via2 = NULL;
            viagem1 = choice1(viagem1,atual);
            viagem2 = choice2(viagem2,atual);
            via1 = cria_viagem1(atual,viagem1,via1);
            via2 = cria_viagem2(atual,viagem2,via2);
            if (strcmp(atual->cidade,atual->city3)!=0) {
                viagem = choice(viagem,atual);
                via = cria_viagem(atual,viagem,via);
                printf("--------------------------------%s---------------------------------\n",atual->cidade);
                print_via(via);
            }
            else{
                viagem = choice3(viagem,atual);
                via = cria_viagem3(atual,viagem,via);
                printf("--------------------------------%s---------------------------------\n",atual->city3);
                print_via(via);
            }
            printf("--------------------------------%s---------------------------------\n",atual->city1);
            print_via(via1);
            printf("--------------------------------%s---------------------------------\n",atual->city2);
            print_via(via2);
            totalUtili = totalUtilizadores();
            local = localUtilizador(atual);
            hot += hotPdi(via,atual->cidade);
            hot += hotPdi(via1,atual->city1);
            hot += hotPdi(via2,atual->city2);
            pontosIncluidos = totalPreferencias(atual);
            totalPontos = contaPontos();
            p1 = (local*100)/totalUtili;
            p2 = (hot*100)/totalUtili;
            p3 = (pontosIncluidos/totalPontos)*100;
            printf("Taxas:\n\t\tPercentagem de utilizadores que tem pelo menos 1 local favorito entre os incluidos na viagem: %d\n",p1);
            printf("\t\tPercentagem de utilizadores cujo PdI hot esta incluido nesta viagem: %d\n",p2);
            printf("\t\tPercentagem das preferencias de PdI: %d\n",p3);
            printf("\t\tMedia das Taxas: %d\n\n\n",(p1+p2+p3)/3);
            inicia(atual);
            return;
        }
    }
    if (aux==6) {
        return;
    }
}


void gravaUtilizador(Utilizador *novo){
    FILE *fp = fopen("utilizadores.txt", "a");
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
        return;
    }
    fprintf(fp, "\n%s,", novo->nome);
    fprintf(fp, "%s,", novo->morada);
    fprintf(fp, "%d/%d/%d, ",novo->dia,novo->mes,novo->ano);
    fprintf(fp, "%d, , ,L, , , , ,L, , , , ,L, , , , ,",novo->telefone);
    fclose(fp);
}


int consultaNome(char nome[]){
    char * result,*name, linha[MAXLINHA];
    int aux;
    FILE *fp = fopen("utilizadores.txt", "r");
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
        return 1;
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        if (result){
            name = strtok(result,",");
            aux = strcmp(nome,name);
            if(aux==0){
                printf("O nome ja existe.\n");
                return 1;
            }
        }
    }
    return 0;
}


int confirma(Utilizador *confirma){
    char * result,*nome, linha[MAXLINHA],*morada,*data, *telemovel,*city,*pi,*city1,*city2,*pc11,*pc12,*pc13,*pc21,*pc22,*pc23,*identificador;
    int aux, auxDia, auxMes, auxAno;
    FILE *fp = fopen("utilizadores.txt", "r");
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        if (result) {
            nome = strtok(result,",");
            aux = strcmp(nome,(confirma->nome));
            if(aux==0){
                morada = strtok(NULL, ",");
                data = strtok(NULL, ",");
                telemovel = strtok(NULL, ",");
                city = strtok(NULL, ",");
                pi = strtok(NULL, ",");
                identificador = strtok(NULL,",");
                city1 = strtok(NULL,",");
                pc11 = strtok(NULL,",");
                pc12 = strtok(NULL,",");
                pc13 = strtok(NULL,",");
                identificador = strtok(NULL,",");
                city2 = strtok(NULL,",");
                pc21 = strtok(NULL,",");
                pc22 = strtok(NULL,",");
                pc23 = strtok(NULL,",");
                sscanf(data,"%d/%d/%d",&auxDia,&auxMes,&auxAno);
                sscanf(telemovel,"%d",&(confirma->telefone));
                confirma->dia = auxDia;
                confirma->mes = auxMes;
                confirma->ano = auxAno;
                strcpy(confirma->morada,morada);
                strcpy(confirma->cidade,city);
                strcpy(confirma->pdi,pi);
                strcpy(confirma->city1,city1);
                strcpy(confirma->city2,city2);
                strcpy(confirma->pc11,pc11);
                strcpy(confirma->pc12,pc12);
                strcpy(confirma->pc13,pc13);
                strcpy(confirma->pc21,pc21);
                strcpy(confirma->pc22,pc22);
                strcpy(confirma->pc23,pc23);
                printf("Ola %s\n", nome);
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}


int login(Utilizador *check){
    int aux;
    printf("Nome: ");
    scanf(" %[^\n]", check->nome);
    aux = confirma(check);
    if(aux==0){
        printf("O NOME NAO SE ENCONTRA NA BASE DE DADOS\n");
        utilizador();
        return 0;
    }
    return 1;
}


int verificaCidade(char cidade[],char pdi[] ,char aux, char pasta[]){
    char *result, linha[MAXLINHA], *identificador, *nome, *ponto, auxPonto[] = "PdI",*segundoIden;
    FILE *fp = fopen("locais.txt", "r");
    fseek (fp, 0, SEEK_SET);
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        if (result) {
            identificador = strtok(result,",");
            if (*identificador == aux) {
                nome = strtok(NULL,",");
                if (strcmp(cidade,nome)==0) {
                    do {
                        result = fgets(linha, MAXLINHA, fp);
                        segundoIden = strtok(result,",");
                        if (strcmp(identificador,auxPonto)==0) {
                            ponto = strtok(NULL, ",");
                            if (strcmp(ponto,pdi)==0) {
                                fclose(fp);
                                return 1;
                            }
                        }
                    }while (*segundoIden!=aux);
                }
            }
        }
    }
    fclose(fp);
    return 0;
}


int checkCity(char cidade[]){
    char *result, linha[MAXLINHA], *identificador, *nome,aux[] = "L";
    FILE *fp = fopen("locais.txt", "r");
    fseek (fp, 0, SEEK_SET);
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        if (result) {
            identificador = strtok(result,",");
            if (strcmp(identificador,aux)==0) {
                nome = strtok(NULL,",");
                if (strcmp(cidade,nome)==0) {
                    return 1;
                }
            }
        }
    }
    fclose(fp);
    return 0;
}


int verifica(List lista,char city[]){
    List actual;
    actual = lista;
    while(actual->next != NULL){
        if (strcmp(actual->info,city)==0) {
            return 1;
        }
        actual= actual->next;
    }
    if (strcmp(actual->info,city)==0) {
        return 1;
    }
    return 0;
}


List ordemAlfa(List lista){
    FILE *fp = fopen("locais.txt", "r");
    List novo,atual, ant;
    int auxPop, i;
    char *result,*string,*cidade,*popularidade,linha[MAXLINHA], identificador[]="L";
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        string = strtok(result,",");
        if (strcmp(string,identificador)==0) {
            novo = (List)malloc(sizeof(List_node));
            cidade = strtok(NULL, ",");
            strcpy(novo->info, cidade);
            popularidade = strtok(NULL, ",");
            auxPop=0;
            i=0;
            while(popularidade[i]!='\0'){
                auxPop = auxPop*10 + (popularidade[i]-'0');
                i++;
            }
            novo->pop = auxPop;
            novo->next = NULL;
            if (lista==NULL) {
                lista = novo;
            }
            else{

                atual = lista;
                ant = NULL;
                while((atual!=NULL) && (strcmp(novo->info,atual->info)>0)){
                    ant=atual;
                    atual = atual->next;
                }
                if (ant != NULL) {
                    ant->next = novo;
                }
                else {
                    lista = novo;
                }
                novo->next = atual;

            }
        }
    }
    fclose(fp);
    return lista;
}


List leficheiro(List lista){
    FILE *fp = fopen("locais.txt", "r");
    List novo,atual, ant;
    int auxPop, i;
    char *result,*string,*cidade,*popularidade,linha[MAXLINHA], identificador[]="L";
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        string = strtok(result,",");
        if (strcmp(string,identificador)==0) {
            novo = (List)malloc(sizeof(List_node));
            cidade = strtok(NULL, ",");
            strcpy(novo->info, cidade);
            popularidade = strtok(NULL, ",");
            auxPop=0;
            i=0;
            while(popularidade[i]!='\0'){
                auxPop = auxPop*10 + (popularidade[i]-'0');
                i++;
            }
            novo->pop = auxPop;
            novo->next = NULL;
            if (lista==NULL) {
                lista = novo;
            }
            else{

                atual = lista;
                ant = NULL;
                while((atual!=NULL) && (novo->pop < atual->pop)){
                    ant=atual;
                    atual = atual->next;
                }
                if(atual==NULL){
                    ant->next = novo;
                }
                else{
                    if(novo->pop == atual->pop){
                        while((atual!=NULL) && (strcmp(novo->info,atual->info)>0) && (atual->pop == novo->pop)){
                            ant=atual;
                            atual = atual->next;
                        }
                    }
                    if (ant != NULL) {
                        ant->next = novo;
                    }
                    else {
                        lista = novo;
                    }
                    novo->next = atual;
                }
            }
        }
    }
    fclose(fp);
    return lista;
}


Viagem alfa(Viagem viagem, char cidade[]){
    char *result, linha[MAXLINHA],*city, *identificador,*pdi,*desc,*inicio, *fim, *pop,aux1[]="L", aux2[]="PdI", aux3[]="Descricao", aux4[]="Horario", aux5[]="Popularidade";
    int i, popAux;
    Viagem atual, novo, ant;
    FILE *fp = fopen("locais.txt", "r");
    fseek (fp, 0, SEEK_SET);
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        identificador = strtok(result, ",");
        if (strcmp(identificador, aux1)==0) {
            city = strtok(NULL,",");
            if (strcmp(city, cidade)==0) {
                do{
                    result = fgets(linha, MAXLINHA, fp);
                    identificador = strtok(result, ",");
                    if (strcmp(aux2,identificador)==0) {
                        novo = (Viagem)malloc(sizeof(Viagem_no));
                        strcpy(novo->cidade,cidade);
                        pdi = strtok(NULL,",");
                        strcpy(novo->ponto,pdi);
                    }
                    if (strcmp(aux3,identificador)==0) {
                        desc = strtok(NULL,",");
                        strcpy(novo->descricao,desc);
                    }
                    if (strcmp(aux4,identificador)==0) {
                        inicio = strtok(NULL,",");
                        fim = strtok(NULL, ",");
                        strcpy(novo->entrada,inicio);
                        strcpy(novo->saida,fim);
                    }
                    if (strcmp(aux5,identificador)==0) {
                        pop = strtok(NULL,",");
                        popAux=0;
                        i=0;
                        while(pop[i]!='\0'){
                            popAux = popAux*10 +(pop[i]-'0');
                            i++;
                        }
                        novo->popularidade = popAux;
                        novo->next = NULL;
                        if (viagem==NULL) {
                            viagem = novo;
                        }
                        else{

                            atual = viagem;
                            ant = NULL;
                            while((atual!=NULL) && (strcmp(novo->ponto,atual->ponto)>0)){
                                ant=atual;
                                atual = atual->next;
                            }
                            if (ant != NULL) {
                                ant->next = novo;
                            }
                            else {
                                viagem = novo;
                            }
                            novo->next = atual;

                        }
                    }
                }while(strcmp(identificador,aux1)!=0);
            }
        }
    }
    fclose(fp);
    return viagem;
}


Viagem gera_viagem(Viagem viagem, char cidade[]){
    char *result, linha[MAXLINHA],*city, *identificador,*pdi,*desc,*inicio, *fim, *pop,aux1[]="L", aux2[]="PdI", aux3[]="Descricao", aux4[]="Horario", aux5[]="Popularidade";
    int i, popAux;
    Viagem atual, novo, ant;
    FILE *fp = fopen("locais.txt", "r");
    fseek (fp, 0, SEEK_SET);
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        identificador = strtok(result, ",");
        if (strcmp(identificador, aux1)==0) {
            city = strtok(NULL,",");
            if (strcmp(city, cidade)==0) {
                do{
                    result = fgets(linha, MAXLINHA, fp);
                    identificador = strtok(result, ",");
                    if (strcmp(aux2,identificador)==0) {
                        novo = (Viagem)malloc(sizeof(Viagem_no));
                        strcpy(novo->cidade,cidade);
                        pdi = strtok(NULL,",");
                        strcpy(novo->ponto,pdi);
                    }
                    if (strcmp(aux3,identificador)==0) {
                        desc = strtok(NULL,",");
                        strcpy(novo->descricao,desc);
                    }
                    if (strcmp(aux4,identificador)==0) {
                        inicio = strtok(NULL,",");
                        fim = strtok(NULL, ",");
                        strcpy(novo->entrada,inicio);
                        strcpy(novo->saida,fim);
                    }
                    if (strcmp(aux5,identificador)==0) {
                        pop = strtok(NULL,",");
                        popAux=0;
                        i=0;
                        while(pop[i]!='\0'){
                            popAux = popAux*10 +(pop[i]-'0');
                            i++;
                        }
                        novo->popularidade = popAux;
                        novo->next = NULL;
                        if (viagem==NULL) {
                            viagem = novo;
                        }
                        else{
                            atual = viagem;
                            ant = NULL;
                            while((atual!=NULL)&&(novo->popularidade < atual->popularidade)){
                                ant = atual;
                                atual = atual->next;
                            }
                            if (atual==NULL) {
                                ant->next = novo;
                            }
                            else{
                                if (novo->popularidade==atual->popularidade) {
                                    while((atual!=NULL) && (strcmp(novo->ponto,atual->ponto)>0) && (novo->popularidade==atual->popularidade)){
                                        ant = atual;
                                        atual = atual->next;
                                    }
                                }
                                if (ant != NULL) {
                                    ant->next = novo;
                                }
                                else {
                                    viagem = novo;
                                }
                                novo->next = atual;
                            }
                        }
                    }
                }while(strcmp(identificador,aux1)!=0);
            }
        }
    }
    fclose(fp);
    return viagem;
}


void print_viagem(Viagem lista){
    Viagem act;
    act = lista;
    while (act->next!=NULL) {
        printf("----------------------------------\n");
        printf("\t\t\tNome: %s\n\t\t\tDescricao: %s\n\t\t\tHorario entrada: %s\n\t\t\tHorario saida: %s\n\t\t\tPopularidade: %d\n",act->ponto, act->descricao,act->entrada,act->saida ,act->popularidade);
        printf("----------------------------------\n");
        act  = act -> next;
    }
    printf("----------------------------------\n");
    printf("\t\t\tNome: %s\n\t\t\tDescricao: %s\n\t\t\tHorario entrada: %s\n\t\t\tHorario saida: %s\n\t\t\tPopularidade: %d\n",act->ponto, act->descricao,act->entrada,act->saida ,act->popularidade);
    printf("----------------------------------\n");
}


void print_lista(List lista){
    List act;
    act = lista;
    while (act->next!=NULL) {
        printf("%s\n",act->info);
        act  = act -> next;
    }
    printf("%s\n",act->info);
}


void acabaLocais(char pasta1[],char pastinha[]){
    char *result2,linha2[MAXLINHA];
    FILE *fp2 = fopen(pastinha, "w");
    FILE *fp = fopen(pasta1, "r");
    fseek (fp, 0L, SEEK_SET);
    fseek (fp2, 0L, SEEK_SET);
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO\n");
    }
    while (!feof(fp)) {
        result2 = fgets(linha2,MAXLINHA,fp);
        fprintf(fp2,"%s",result2);
    }
    fclose(fp);
    fclose(fp2);
    remove(pasta1);
}


void alteraNum(char pastinha[],long int position, int num){
    FILE *fp = fopen(pastinha, "r");
    FILE *fp2 = fopen("locaisnovos.txt", "w");
    char *result, linha[MAXLINHA],total=0;
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);

        total++;
        if (total==position) {
            fprintf(fp2,"Popularidade,%d,\n",num);
        }
        else{
            fprintf(fp2,"%s",result);
        }
    }
    fclose(fp2);
    fclose(fp);
    acabaLocais("locaisnovos.txt",pastinha);
}


void aumentaPopCidade(long int pos, int num, char cidade[]){
    FILE *fp = fopen("locais.txt", "r");
    FILE *fp2 = fopen("locaisnovos.txt", "w");
    char *result, linha[MAXLINHA];
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        if (ftell(fp)!=pos) {
            fprintf(fp2,"%s",result);
        }
        else{
            fprintf(fp2,"L,%s,%d,\n",cidade,num);
        }
    }
    fclose(fp2);
    fclose(fp);
    acabaLocais("locaisnovos.txt","locais.txt");
}


void retiraPopCidade(Utilizador *atual){
    char *result, linha[MAXLINHA], *city, *identificador, aux[]="L",*popularidade;
    int pop=0, i=0;
    FILE *fp = fopen("locais.txt", "r");
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
    }
    while (!feof(fp)) {
        result = fgets(linha,MAXLINHA, fp);
        if (result) {
            identificador = strtok(result, ",");
            if (strcmp(identificador,aux)==0) {
                city = strtok(NULL,",");
                if (strcmp(city,atual->cidade)==0) {
                    popularidade = strtok(NULL,",");
                    while(popularidade[i]!='\0'){
                        pop = pop*10 + (popularidade[i]-'0');
                        i++;
                    }
                    pop-=1;
                    aumentaPopCidade(ftell(fp),pop,atual->cidade);
                    fclose(fp);
                    return;
                }
            }
        }
    }
}


void retiraPop(Utilizador *atual){
    char *result, linha[MAXLINHA], *city,*interesse,*identificador,*segIden,auxPonto[] = "PdI",*terIden,auxPop[]="Popularidade",auxCidade[]="L", *pop;
    FILE *fp = fopen("locais.txt", "r");
    int popu=0, i=0,line=0;
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
    }
    fseek(fp,0L,SEEK_SET);
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        line++;
        if (result) {
            identificador = strtok(result, ",");
            if (strcmp(auxCidade,identificador)==0) {
                city = strtok(NULL,",");
                if (strcmp(city,atual->cidade)==0) {
                    do {
                        result = fgets(linha, MAXLINHA, fp);
                        line++;
                        segIden = strtok(result,",");
                        if (strcmp(segIden,auxPonto)==0) {
                            interesse = strtok(NULL,",");
                            if (strcmp(interesse,(atual->pdi))==0) {
                                do{
                                    result = fgets(linha, MAXLINHA, fp);
                                    line++;
                                    terIden = strtok(result,",");
                                    if (strcmp(terIden,auxPop)==0) {
                                        pop = strtok(NULL,",");
                                        while ((pop[i])!='\0') {
                                            popu = popu*10+(pop[i]-'0');
                                            i++;
                                        }
                                        popu-=5;
                                        alteraNum("locais.txt",line,popu);
                                        fclose(fp);
                                        return;
                                    }
                                }while(strcmp(terIden,auxPonto)!=0);
                            }
                        }
                    }while (strcmp(segIden,auxCidade)!=0);
                }
            }
        }
    }
    fclose(fp);
}


void guardaPdi(Escolhe * ponto){
    char *result, linha[MAXLINHA], *city,*interesse,*identificador,*segIden,auxPonto[] = "PdI",*terIden,auxPop[]="Popularidade",auxCidade[]="L", *pop, *popCi;
    long int pos;
    FILE *fp = fopen("locais.txt", "r");
    int popularidade=0,i=0,popCity=0,j=0,line=0;;
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE UTILIZADORES\n");
    }
    fseek(fp,0L,SEEK_SET);
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        line++;
        if (result) {
            identificador = strtok(result, ",");
            if (strcmp(auxCidade,identificador)==0){
                city = strtok(NULL,",");
                popCi = strtok(NULL, ",");
                pos = ftell(fp);
                if (strcmp(city,ponto->cidade)==0) {
                    while(popCi[j]!='\0'){
                        popCity = popCity*10 +(popCi[j]-'0');
                        j++;
                    }
                    popCity+=1;
                    aumentaPopCidade(pos,popCity,city);
                    do {
                        result = fgets(linha, MAXLINHA, fp);
                        line++;
                        segIden = strtok(result,",");
                        if (strcmp(segIden,auxPonto)==0) {
                            interesse = strtok(NULL,",");
                            if (strcmp(interesse,(ponto->local))==0) {
                                do{
                                    result = fgets(linha, MAXLINHA, fp);
                                    line++;
                                    terIden = strtok(result,",");
                                    if (strcmp(terIden,auxPop)==0) {
                                        pop = strtok(NULL,",");
                                        while ((pop[i])!='\0') {
                                            popularidade = popularidade*10+((pop[i])-'0');
                                            i++;
                                        }
                                        popularidade+=5;
                                        alteraNum("locais.txt",line,popularidade);
                                        fclose(fp);
                                        return;
                                    }
                                }while(strcmp(terIden,auxPonto)!=0);
                            }
                        }
                    }while (strcmp(segIden,auxCidade)!=0);
                }
            }
        }
    }
    fclose(fp);
}


void apagaFichU(){
    char *result2,linha2[MAXLINHA];
    FILE *fp2 = fopen("utilizadores.txt", "w");
    FILE *fp = fopen("utilizadoresnovos.txt", "r");
    fseek (fp, 0L, SEEK_SET);
    fseek (fp2, 0L, SEEK_SET);
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result2 = fgets(linha2,MAXLINHA,fp);
        fprintf(fp2,"%s",result2);
    }
    fclose(fp);
    fclose(fp2);
    remove("utilizadoresnovos.txt");
}


void guardaUti(Utilizador * atual, Escolhe * paraGuardar){
    FILE *fp = fopen("utilizadores.txt", "r");
    FILE *fp2 = fopen("utilizadoresnovos.txt", "w");
    char *result, linha[MAXLINHA],*nome,*morada,*data,*telemovel,*auxCidade,*auxPdi,aux[MAXLINHA];

    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        strcpy(aux,result);
        nome = strtok(result,",");
        morada = strtok(NULL, ",");
        data = strtok(NULL, ",");
        telemovel = strtok(NULL, ",");
        auxCidade = strtok(NULL, ",");
        auxPdi = strtok(NULL,",");
        if (strcmp(nome, atual->nome)!=0) {
            fprintf(fp2,"%s",aux);
        }
        if (strcmp(nome,atual->nome)==0) {
            fprintf(fp2,"%s,%s,%d/%d/%d,%d,%s,%s,L,%s,%s,%s,%s,L,%s,%s,%s,%s,L,%s,%s,%s,%s,",atual->nome, atual->morada, atual->dia, atual->mes, atual->ano, atual->telefone,paraGuardar->cidade, paraGuardar->local,atual->city1,atual->pc11,atual->pc12,atual->pc13,atual->city2,atual->pc21,atual->pc22,atual->pc23,atual->city3,atual->pc31,atual->pc32,atual->pc33);
        }
    }
    fclose(fp);
    fclose(fp2);
    apagaFichU();
}


void prefer(Utilizador *atual){
    int aux;
    Escolhe pdInteresse;
    char city[MAXCIDADE], pontodi[MAXCIDADE];
    printf("CIDADE: ");
    scanf(" %[^\n]", city);
    printf("Ponto de Interesse: ");
    scanf(" %[^\n]", pontodi);
    if ((strcmp(atual->cidade,city)==0)&&(strcmp(atual->pdi,pontodi)==0)&&(strcmp(atual->cidade," ")!=0)&&(strcmp(atual->pdi," ")!=0)){
        printf("Este ja e o seu ponto de interesse\n");
    }
    else{
        aux = verificaCidade(city, pontodi,'L', "locais.txt");
        if (aux==0) {
            printf("O ponto de interesse nao foi encontrado.\n");
        }
        else if(aux==1){
            if (strcmp(city,atual->city1)==0) {
                strcpy(atual->city1," ");
                strcpy(atual->pc11," ");
                strcpy(atual->pc12," ");
                strcpy(atual->pc13," ");
            }
            else if (strcmp(city,atual->city2)==0) {
                strcpy(atual->city2," ");
                strcpy(atual->pc21," ");
                strcpy(atual->pc22," ");
                strcpy(atual->pc23," ");
            }
            strcpy(atual->city3," ");
            strcpy(atual->pc31," ");
            strcpy(atual->pc32," ");
            strcpy(atual->pc33," ");
            strcpy(pdInteresse.cidade,city);
            strcpy(pdInteresse.local,pontodi);
            guardaPdi(&pdInteresse);
            retiraPop(atual);
            retiraPopCidade(atual);
            strcpy((atual->cidade),city);
            strcpy((atual->pdi),pontodi);
            guardaUti(atual,&pdInteresse);
        }
    }
    inicia(atual);
    return;
}


void escolhe_cidade_alfa(List listaPop, Viagem viagem){
    char city[MAXCIDADE];
    int estado;
    printf("Escolha uma cidade: ");
    scanf(" %[^\n]", city);
    estado = verifica(listaPop,city);
    if (estado==1) {
        viagem = NULL;
        viagem=alfa(viagem,city);
        print_viagem(viagem);
    }
    else{
        printf("A cidade nao se encontra na lista.\n");
        escolhe_cidade_alfa(listaPop, viagem);
        return;
    }
}


Travel cria_viagem3(Utilizador *atual,Viagem viagem,Travel via){
    Viagem actual;
    Travel act;
    Travel novo;
    Travel pr;
    Travel prox;
    Travel proxprox;
    int i = 0;
    actual = viagem;
    novo = (Travel)malloc(sizeof(Travel_no));
    novo->next = NULL;
    actual = viagem;
    act = via;
    if (strcmp(atual->city3,viagem->cidade)==0 && strcmp(atual->city3," ")!=0 && strcmp(atual->pc31," ")!= 0 && strcmp(atual->pc32," ")!= 0 && strcmp(atual->pc33," ")!= 0 && strcmp(atual->city3,"")!=0 && strcmp(atual->pc31,"")!= 0 && strcmp(atual->pc32,"")!= 0 && strcmp(atual->pc33,"")!=0) {
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        proxprox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = proxprox;
        proxprox->next = NULL;
        if (via==NULL) {
            strcpy(pr->p1,atual->pc31);
            strcpy(prox->p1,atual->pc32);
            strcpy(proxprox->p1,atual->pc33);
            via = pr;
        }
    }
    else if(strcmp(atual->city3,viagem->cidade)==0 && strcmp(atual->city3," ")!=0 && strcmp(atual->pc31," ")!= 0 && strcmp(atual->pc32," ")!= 0 && (strcmp(atual->pc33," ")== 0 || strcmp(atual->pc33,"")==0) && strcmp(atual->city3,"")!=0 && strcmp(atual->pc31,"")!= 0 && strcmp(atual->pc32,"")!= 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if (via==NULL) {
            strcpy(pr->p1,atual->pc31);
            strcpy(prox->p1,atual->pc32);
            while(actual!=NULL){
                if (strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0 ) {
                    strcpy(novo->p1,actual->ponto);
                    break;
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    else if(strcmp(atual->city3,viagem->cidade)==0 && strcmp(atual->city3," ")!=0 && strcmp(atual->pc31," ")!= 0 && (strcmp(atual->pc32," ")== 0 || strcmp(atual->pc32,"")==0) && (strcmp(atual->pc33," ")== 0 || strcmp(atual->pc33,"")==0) && strcmp(atual->city3,"")!=0 && strcmp(atual->pc31,"")!= 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if(via==NULL){
            strcpy(pr->p1,atual->pc31);
            while (i<2 && actual!=NULL ) {
                if (i<1) {
                    if (strcmp(actual->ponto,pr->p1)!=0){
                        strcpy(prox->p1,actual->ponto);
                        i++;
                    }
                }
                else if (i==1) {
                    if (strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0 ) {
                        strcpy(novo->p1,actual->ponto);
                        i++;
                        break;
                    }
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    else if(strcmp(atual->city3,viagem->cidade)==0 && strcmp(atual->city3," ")!=0 && (strcmp(atual->pc31," ")!= 0 || strcmp(atual->pc31,"")==0) && (strcmp(atual->pc32," ")== 0 || strcmp(atual->pc32,"")==0) && (strcmp(atual->pc33," ")== 0 || strcmp(atual->pc33,"")==0) && strcmp(atual->city3,"")!=0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if(via==NULL){
            while (i<3 && actual!=NULL ) {
                if (i<1) {
                    strcpy(pr->p1,actual->ponto);
                    i++;
                }
                else if (i==1) {
                    if (strcmp(actual->ponto,pr->p1)!=0) {
                        strcpy(prox->p1,actual->ponto);
                        i++;
                    }
                }
                else if(i==2){
                    if(strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0){
                        strcpy(novo->p1,actual->ponto);
                        i++;
                        break;
                    }
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    return via;
}


Travel cria_viagem2(Utilizador *atual,Viagem viagem,Travel via){
    Viagem actual;
    Travel act;
    Travel novo;
    Travel pr;
    Travel prox;
    Travel proxprox;
    int i = 0;
    actual = viagem;
    novo = (Travel)malloc(sizeof(Travel_no));
    novo->next = NULL;
    actual = viagem;
    act = via;
    if (strcmp(atual->city2,viagem->cidade)==0 && strcmp(atual->city2," ")!=0 && strcmp(atual->pc21," ")!= 0 && strcmp(atual->pc22," ")!= 0 && strcmp(atual->pc23," ")!= 0) {
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        proxprox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = proxprox;
        proxprox->next = NULL;
        if (via==NULL) {
            strcpy(pr->p1,atual->pc21);
            strcpy(prox->p1,atual->pc22);
            strcpy(proxprox->p1,atual->pc23);
            via = pr;
        }
    }
    else if(strcmp(atual->city2,viagem->cidade)==0 && strcmp(atual->city2," ")!=0 && strcmp(atual->pc21," ")!= 0 && strcmp(atual->pc22," ")!= 0 && strcmp(atual->pc23," ")== 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if (via==NULL) {
            strcpy(pr->p1,atual->pc21);
            strcpy(prox->p1,atual->pc22);
            while(actual!=NULL){
                if (strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0 ) {
                    strcpy(novo->p1,actual->ponto);
                    break;
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    else if(strcmp(atual->city2,viagem->cidade)==0 && strcmp(atual->city2," ")!=0 && strcmp(atual->pc21," ")!= 0 && strcmp(atual->pc22," ")== 0 && strcmp(atual->pc23," ")== 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if(via==NULL){
            strcpy(pr->p1,atual->pc21);
            while (i<2 && actual!=NULL ) {
                if (i<1) {
                    if (strcmp(actual->ponto,pr->p1)!=0){
                        strcpy(prox->p1,actual->ponto);
                        i++;
                    }
                }
                else if (i==1) {
                    if (strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0 ) {
                        strcpy(novo->p1,actual->ponto);
                        i++;
                        break;
                    }
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    else if(strcmp(atual->city2,viagem->cidade)==0 && strcmp(atual->city2," ")!=0 && strcmp(atual->pc21," ")== 0 && strcmp(atual->pc22," ")== 0 && strcmp(atual->pc23," ")== 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if(via==NULL){
            while (i<3 && actual!=NULL ) {
                if (i<1) {
                    strcpy(pr->p1,actual->ponto);
                    i++;
                }
                else if (i==1) {
                    if (strcmp(actual->ponto,pr->p1)!=0) {
                        strcpy(prox->p1,actual->ponto);
                        i++;
                    }
                }
                else if(i==2){
                    if(strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0){
                        strcpy(novo->p1,actual->ponto);
                        i++;
                        break;
                    }
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    return via;
}


Travel cria_viagem1(Utilizador *atual,Viagem viagem,Travel via){
    Viagem actual;
    Travel act;
    Travel novo;
    Travel pr;
    Travel prox;
    Travel proxprox;
    int i = 0;
    actual = viagem;
    novo = (Travel)malloc(sizeof(Travel_no));
    novo->next = NULL;
    actual = viagem;
    act = via;
    if (strcmp(atual->city1,viagem->cidade)==0 && strcmp(atual->city1," ")!=0 && strcmp(atual->pc11," ")!= 0 && strcmp(atual->pc12," ")!= 0 && strcmp(atual->pc13," ")!= 0) {
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        proxprox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = proxprox;
        proxprox->next = NULL;
        if (via==NULL) {
            strcpy(pr->p1,atual->pc11);
            strcpy(prox->p1,atual->pc12);
            strcpy(proxprox->p1,atual->pc13);
            via = pr;
        }
    }
    else if(strcmp(atual->city1,viagem->cidade)==0 && strcmp(atual->city1," ")!=0 && strcmp(atual->pc11," ")!= 0 && strcmp(atual->pc12," ")!= 0 && strcmp(atual->pc13," ")== 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if (via==NULL) {
            strcpy(pr->p1,atual->pc11);
            strcpy(prox->p1,atual->pc12);
            while(actual!=NULL){
                if (strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0 ) {
                    strcpy(novo->p1,actual->ponto);
                    break;
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    else if(strcmp(atual->city1,viagem->cidade)==0 && strcmp(atual->city1," ")!=0 && strcmp(atual->pc11," ")!= 0 && strcmp(atual->pc12," ")== 0 && strcmp(atual->pc13," ")== 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if(via==NULL){
            strcpy(pr->p1,atual->pc11);
            while (i<2 && actual!=NULL ) {
                if (i<1) {
                    if (strcmp(actual->ponto,pr->p1)!=0){
                        strcpy(prox->p1,actual->ponto);
                        i++;
                    }
                }
                else if (i==1) {
                    if (strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0 ) {
                        strcpy(novo->p1,actual->ponto);
                        i++;
                        break;
                    }
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    else if(strcmp(atual->city1,viagem->cidade)==0 && strcmp(atual->city1," ")!=0 && strcmp(atual->pc11," ")== 0 && strcmp(atual->pc12," ")== 0 && strcmp(atual->pc13," ")== 0){
        novo = (Travel)malloc(sizeof(Travel_no));
        pr = (Travel)malloc(sizeof(Travel_no));
        prox = (Travel)malloc(sizeof(Travel_no));
        pr->next = prox;
        prox->next = novo;
        novo->next = NULL;
        if(via==NULL){
            while (i<3 && actual!=NULL ) {
                if (i<1) {
                    strcpy(pr->p1,actual->ponto);
                    i++;
                }
                else if (i==1) {
                    if (strcmp(actual->ponto,pr->p1)!=0) {
                        strcpy(prox->p1,actual->ponto);
                        i++;
                    }
                }
                else if(i==2){
                    if(strcmp(actual->ponto,pr->p1)!=0 && strcmp(actual->ponto,prox->p1)!=0){
                        strcpy(novo->p1,actual->ponto);
                        i++;
                        break;
                    }
                }
                actual = actual->next;
            }
            via = pr;
        }
    }
    return via;
}


Travel cria_viagem(Utilizador *atual,Viagem viagem,Travel via){
    Viagem actual;
    Travel act;
    Travel novo;
    int i=0;
    novo = (Travel)malloc(sizeof(Travel_no));
    novo->next = NULL;
    actual = viagem;
    act = via;
    if (strcmp(atual->cidade,viagem->cidade)==0) {
        novo = (Travel)malloc(sizeof(Travel_no));
        novo->next = NULL;
        strcpy(novo->p1,atual->pdi);
        while(i<3){
            if (via==NULL) {
                act = novo;
                via = act;
                i++;
            }
            else{
                while ((actual!=NULL)&&(i<3)) {
                    if (strcmp(actual->ponto,atual->pdi)!=0) {
                        novo = (Travel)malloc(sizeof(Travel_no));
                        novo->next = NULL;
                        strcpy(novo->p1,actual->ponto);
                        act->next = novo;
                        act = act->next;
                        i++;
                    }
                    actual = actual->next;
                }
            }
        }
    }
    else{
        while((i<3)&&(actual!=NULL)){
            novo = (Travel)malloc(sizeof(Travel_no));
            novo->next = NULL;
            strcpy(novo->p1,actual->ponto);
            if (via==NULL) {
                act = novo;
                via = act;
                i++;
            }
            else{
                act->next = novo;
                act = act->next;
                i++;
            }
            actual = actual->next;
        }
    }
    return via;
}


Viagem choice3(Viagem viagem,Utilizador *atual){
    char city[MAXCIDADE];
    strcpy(city,atual->city3);
    viagem = NULL;
    viagem=gera_viagem(viagem,city);
    return viagem;
}


Viagem choice2(Viagem viagem,Utilizador *atual){
    char city[MAXCIDADE];
    strcpy(city,atual->city2);
    viagem = NULL;
    viagem=gera_viagem(viagem,city);
    return viagem;
}


Viagem choice1(Viagem viagem,Utilizador *atual){
    char city[MAXCIDADE];
    strcpy(city,atual->city1);
    viagem = NULL;
    viagem=gera_viagem(viagem,city);
    return viagem;
}


Viagem choice(Viagem viagem,Utilizador *atual){
    char city[MAXCIDADE];
    strcpy(city,atual->cidade);
    viagem = NULL;
    viagem=gera_viagem(viagem,city);
    return viagem;
}


void escolhe_cidade(List listaPop, Viagem viagem){
    char city[MAXCIDADE];
    int estado;
    printf("Escolha uma cidade: ");
    scanf(" %[^\n]", city);
    estado = verifica(listaPop,city);
    if (estado==1) {
        viagem = NULL;
        viagem=gera_viagem(viagem,city);
        print_viagem(viagem);
        return;
    }
    else{
        printf("A cidade nao se encontra na lista.\n");
        escolhe_cidade(listaPop, viagem);
        return;
    }

}


void guardaPrefeCidade(Utilizador * atual){
    FILE *fp = fopen("utilizadores.txt","r");
    FILE *fp2 = fopen("novos.txt","w");
    char *result, linha[MAXLINHA],*nome, line[MAXLINHA];
    while(!feof(fp)){
        result = fgets(linha, MAXLINHA, fp);
        strcpy(line,result);
        nome = strtok(result,",");
        if (strcmp(atual->nome,nome)==0) {
            fprintf(fp2,"%s,%s,%d/%d/%d,%d,%s,%s,L,%s,%s,%s,%s,L,%s,%s,%s,%s,L,%s,%s,%s,%s,",atual->nome,atual->morada,atual->dia,atual->mes,atual->ano,atual->telefone,atual->cidade,atual->pdi,atual->city1,atual->pc11,atual->pc12,atual->pc13,atual->city2,atual->pc21,atual->pc22,atual->pc23,atual->city3,atual->pc31,atual->pc32,atual->pc33);
        }
        else{
            fprintf(fp2,"%s",line);
        }
    }
    fclose(fp2);
    fclose(fp);
    acabaLocais("novos.txt","utilizadores.txt");
    return;
}


void alteraNumero(char pastinha[],long int pos, int num){
    FILE *fp = fopen(pastinha, "r");
    FILE *fp2 = fopen("locaisnovos.txt", "w");
    char *result, linha[MAXLINHA];
    if (fp==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DE LOCAIS\n");
    }
    while (!feof(fp)) {
        result = fgets(linha, MAXLINHA, fp);
        if (ftell(fp)!=pos){
            fprintf(fp2,"%s",result);
        }
        else{
            fprintf(fp2,"Popularidade,%d,\n",num);
        }
    }
    fclose(fp2);
    fclose(fp);
    acabaLocais("locaisnovos.txt",pastinha);
}


void retiraPopularidade(Utilizador *atual){
    FILE *fp = fopen("locais.txt","r");
    char *result, linha[MAXLINHA],*cidade,*popu,*pdi,*identificador;
    int pop = 0,i;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        identificador = strtok(result,",");
        if (strcmp(identificador,"L")==0) {
            cidade = strtok(NULL,",");
            if (strcmp(cidade,atual->city1)==0) {
                popu = strtok(NULL,",");
                pop = 0;
                for (i=0; popu[i]!='\0'; i++) {
                    pop = pop*10 +(popu[i]-'0');
                }
                pop--;
                aumentaPopCidade(ftell(fp),pop,atual->city1);
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"PdI")==0) {
                        pdi = strtok(NULL,",");
                        if (strcmp(pdi,atual->pc11)==0||strcmp(pdi,atual->pc12)==0||strcmp(pdi,atual->pc13)==0) {
                            do{
                                result = fgets(linha,MAXLINHA,fp);
                                identificador = strtok(result,",");
                            }while(strcmp(identificador,"Popularidade")!=0);
                            popu = strtok(NULL,",");
                            pop = 0;
                            for (i=0; popu[i]!='\0'; i++) {
                                pop = pop*10 +(popu[i]-'0');
                            }
                            pop--;
                            alteraNumero("locais.txt",ftell(fp),pop);
                            pop = 0;
                        }
                    }
                }while(strcmp(identificador,"L")!=0);
            }
            else if (strcmp(cidade,atual->city2)==0) {
                popu = strtok(NULL,",");
                pop = 0;
                for (i=0; popu[i]!='\0'; i++) {
                    pop = pop*10 +(popu[i]-'0');
                }
                pop--;
                aumentaPopCidade(ftell(fp),pop,atual->city2);
                pop = 0;
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"PdI")==0) {
                        pdi = strtok(NULL,",");
                        if (strcmp(pdi,atual->pc21)==0||strcmp(pdi,atual->pc22)==0||strcmp(pdi,atual->pc23)==0) {
                            do{
                                result = fgets(linha,MAXLINHA,fp);
                                identificador = strtok(result,",");
                            }while(strcmp(identificador,"Popularidade")!=0);
                            popu = strtok(NULL,",");
                            pop = 0;
                            for (i=0; popu[i]!='\0'; i++) {
                                pop = pop*10 +(popu[i]-'0');
                            }
                            pop--;
                            alteraNumero("locais.txt",ftell(fp),pop);
                            pop = 0;
                        }
                    }
                }while(strcmp(identificador,"L")!=0);

            }
            else if (strcmp(cidade,atual->city3)==0) {
                popu = strtok(NULL,",");
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"PdI")==0) {
                        pdi = strtok(NULL,",");
                        if (strcmp(pdi,atual->pc32)==0||strcmp(pdi,atual->pc33)==0) {
                            do{
                                result = fgets(linha,MAXLINHA,fp);
                                identificador = strtok(result,",");
                            }while(strcmp(identificador,"Popularidade")!=0);
                            popu = strtok(NULL,",");
                            pop = 0;
                            for (i=0; popu[i]!='\0'; i++) {
                                pop = pop*10 +(popu[i]-'0');
                            }
                            pop--;
                            alteraNumero("locais.txt",ftell(fp),pop);
                            pop = 0;
                        }
                    }
                }while(strcmp(identificador,"L")!=0);
            }
        }

    }
}


void aumentaPopularidade(Utilizador *atual){
    FILE *fp = fopen("locais.txt","r");
    char *result, linha[MAXLINHA],*cidade,*popu,*pdi,*identificador;
    int pop = 0,i;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        identificador = strtok(result,",");
        if (strcmp(identificador,"L")==0) {
            cidade = strtok(NULL,",");
            if (strcmp(cidade,atual->city1)==0) {
                popu = strtok(NULL,",");
                pop = 0;
                for (i=0; popu[i]!='\0'; i++) {
                    pop = pop*10 +(popu[i]-'0');
                }
                pop++;
                aumentaPopCidade(ftell(fp),pop,atual->city1);
                pop =0;
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"PdI")==0) {
                        pdi = strtok(NULL,",");
                        if (strcmp(pdi,atual->pc11)==0||strcmp(pdi,atual->pc12)==0||strcmp(pdi,atual->pc13)==0) {
                            do{
                                result = fgets(linha,MAXLINHA,fp);
                                identificador = strtok(result,",");
                            }while(strcmp(identificador,"Popularidade")!=0);
                            popu = strtok(NULL,",");
                            pop = 0;
                            for (i=0; popu[i]!='\0'; i++) {
                                pop = pop*10 +(popu[i]-'0');
                            }
                            pop++;
                            alteraNumero("locais.txt",ftell(fp),pop);
                            pop = 0;
                        }
                    }
                }while(strcmp(identificador,"L")!=0);
            }
            else if (strcmp(cidade,atual->city2)==0) {
                popu = strtok(NULL,",");
                pop = 0;
                for (i=0; popu[i]!='\0'; i++) {
                    pop = pop*10 +(popu[i]-'0');
                }
                pop++;
                aumentaPopCidade(ftell(fp),pop,atual->city2);
                pop = 0;
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"PdI")==0) {
                        pdi = strtok(NULL,",");
                        if (strcmp(pdi,atual->pc21)==0||strcmp(pdi,atual->pc22)==0||strcmp(pdi,atual->pc23)==0) {
                            do{
                                result = fgets(linha,MAXLINHA,fp);
                                identificador = strtok(result,",");
                            }while(strcmp(identificador,"Popularidade")!=0);
                            popu = strtok(NULL,",");
                            pop = 0;
                            for (i=0; popu[i]!='\0'; i++) {
                                pop = pop*10 +(popu[i]-'0');
                            }
                            pop++;
                            alteraNumero("locais.txt",ftell(fp),pop);
                            pop = 0;
                        }
                    }
                }while(strcmp(identificador,"L")!=0);
            }
            else if (strcmp(cidade,atual->city3)==0) {
                popu = strtok(NULL,",");
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"PdI")==0) {
                        pdi = strtok(NULL,",");
                        if (strcmp(pdi,atual->pc32)==0||strcmp(pdi,atual->pc33)==0) {
                            do{
                                result = fgets(linha,MAXLINHA,fp);
                                identificador = strtok(result,",");
                            }while(strcmp(identificador,"Popularidade")!=0);
                            popu = strtok(NULL,",");
                            pop = 0;
                            for (i=0; popu[i]!='\0'; i++) {
                                pop = pop*10 +(popu[i]-'0');
                            }
                            pop++;
                            alteraNumero("locais.txt",ftell(fp),pop);
                            pop = 0;
                        }
                    }
                }while(strcmp(identificador,"L")!=0);
            }
        }

    }
}


void preferCidade(Utilizador *atual){
    char city[MAXCIDADE], pdi[MAXCIDADE];
    int checa,opcao;
    printf("Escolha uma cidade: ");
    scanf(" %[^\n]", city);
    checa = checkCity(city);
    if (checa==1) {
        printf("Deseja escolher alguma preferencia dessa cidade (sim-[1],nao-[2]): ");
        do{
            scanf("%d",&opcao);
        }while((opcao!=1) && (opcao!=2));
        if (opcao==2) {
            if (strcmp(city,atual->cidade)==0) {
                printf("ESTA CIDADE JA É O SEU HOTSPOT\n");
            }
            else if(strcmp(atual->city1," ")==0 || strcmp(atual->city1,"")==0){
                strcpy(atual->city1,city);
            }
            else if(strcmp(atual->city2," ")==0 || strcmp(atual->city2,"")==0){
                strcpy(atual->city2,city);
            }
        }
        else if (opcao==1) {
            printf("Escolha uma preferencia: ");
            scanf(" %[^\n]", pdi);
            checa = verificaCidade(city,pdi,'L',"locais.txt");
            if(checa==1){
                retiraPopularidade(atual);
                if (strcmp(city,atual->cidade)==0) {
                    if(strcmp(pdi,atual->pdi)!=0 && strcmp(pdi,atual->pc32)!=0 && strcmp(pdi,atual->pc33)!=0){
                        strcpy(atual->city3,city);
                        strcpy(atual->pc31,atual->pdi);
                        if (strcmp(atual->pc32," ")==0||strcmp(atual->pc32,"")==0) {
                            strcpy(atual->pc32,pdi);
                        }
                        else if(strcmp(atual->pc33," ")==0||strcmp(atual->pc33,"")==0){
                            strcpy(atual->pc33,pdi);
                        }
                        else{
                            strcpy(atual->pc32,pdi);
                        }
                    }
                }
                else if (strcmp(city,atual->city1)==0) {
                    if (strcmp(atual->pc11," ")==0  && strcmp(atual->pc12,pdi)!=0 && strcmp(atual->pc13,pdi)!=0) {
                        strcpy(atual->pc11,pdi);
                    }
                    else if(strcmp(atual->pc12," ")==0  && strcmp(atual->pc11,pdi)!=0 && strcmp(atual->pc13,pdi)!=0){
                        strcpy(atual->pc12,pdi);
                    }
                    else if (strcmp(atual->pc13," ")==0  && strcmp(atual->pc12,pdi)!=0 && strcmp(atual->pc11,pdi)!=0){
                        strcpy(atual->pc13,pdi);
                    }
                    else{
                        if(strcmp(atual->pc13,pdi)!=0 && strcmp(atual->pc11,pdi)!=0 && strcmp(atual->pc12,pdi)!=0){
                            strcpy(atual->pc11,pdi);
                        }
                    }
                }
                else if (strcmp(city,atual->city2)==0) {
                    if (strcmp(atual->pc21," ")==0 && strcmp(atual->pc22,pdi)!=0 && strcmp(atual->pc23,pdi)!=0) {
                        strcpy(atual->pc21,pdi);
                    }
                    else if(strcmp(atual->pc22," ")==0 && strcmp(atual->pc21,pdi)!=0 && strcmp(atual->pc23,pdi)!=0){
                        strcpy(atual->pc22,pdi);
                    }
                    else if (strcmp(atual->pc23," ")==0  && strcmp(atual->pc21,pdi)!=0 && strcmp(atual->pc22,pdi)!=0){
                        strcpy(atual->pc23,pdi);
                    }
                    else{
                        if(strcmp(atual->pc23,pdi)!=0 && strcmp(atual->pc21,pdi)!=0 && strcmp(atual->pc22,pdi)!=0){
                            strcpy(atual->pc21,pdi);
                        }
                    }
                }
                else{
                    if (strcmp(" ",atual->city2)!=0) {
                        strcpy(atual->city1,city);
                        strcpy(atual->pc11,pdi);
                        strcpy(atual->pc12," ");
                        strcpy(atual->pc13," ");
                    }
                    else if ((strcmp(" ",atual->city2)==0)&&(strcmp(" ",atual->city1)!=0)) {
                        strcpy(atual->city2,city);
                        strcpy(atual->pc21,pdi);
                        strcpy(atual->pc22," ");
                        strcpy(atual->pc23," ");
                    }
                    else if((strcmp(" ",atual->city2)==0)&&(strcmp(" ",atual->city1)==0)){
                        strcpy(atual->city1,city);
                        strcpy(atual->pc11,pdi);
                        strcpy(atual->pc12," ");
                        strcpy(atual->pc13," ");
                    }
                }
            }
            else{
                printf("Ponto de interesse nao encontrado.\n");
            }
        }
        else if(opcao==2){
            if (strcmp(atual->city1," ")==0 && strcmp(atual->city2,pdi)!=0) {
                strcpy(atual->city1,city);
                strcpy(atual->pc11," ");
                strcpy(atual->pc12," ");
                strcpy(atual->pc13," ");
            }
            else if(strcmp(atual->city2," ")==0 && strcmp(atual->city1,pdi)!=0){
                strcpy(atual->city2,city);
                strcpy(atual->pc21," ");
                strcpy(atual->pc22," ");
                strcpy(atual->pc23," ");
            }
            else if(strcmp(atual->city2," ")!=0 && strcmp(atual->city1," ")!=0){
                strcpy(atual->city1,city);
                strcpy(atual->pc11," ");
                strcpy(atual->pc12," ");
                strcpy(atual->pc13," ");
            }
            else if(strcmp(atual->city2,pdi)==0 || strcmp(atual->city1,pdi)==0){}
        }
        guardaPrefeCidade(atual);
        aumentaPopularidade(atual);
    }
    else{
        printf("O ponto de interesse nao existe.\n");
        return;
    }
}


int totalUtilizadores(){
    FILE *fp = fopen("utilizadores.txt","r");
    char *result,linha[MAXLINHA];
    int total = 0;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        total++;
    }
    fclose(fp);
    return total;
}


int localUtilizador(Utilizador * atual){
    FILE *fp = fopen("utilizadores.txt","r");
    char *result,linha[MAXLINHA],*ci1,*ci2,*ci3;
    int total = 0;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        ci1 = strtok(result,",");
        ci1 = strtok(NULL,",");
        ci1 = strtok(NULL,",");
        ci1 = strtok(NULL,",");
        ci1 = strtok(NULL,",");
        ci2 = strtok(NULL,",");
        ci2 = strtok(NULL,",");
        ci2 = strtok(NULL,",");
        ci3 = strtok(NULL,",");
        ci3 = strtok(NULL,",");
        ci3 = strtok(NULL,",");
        ci3 = strtok(NULL,",");
        ci3 = strtok(NULL,",");
        if (strcmp(ci1,atual->cidade)==0 || strcmp(ci2,atual->cidade)==0 || strcmp(ci3,atual->cidade)==0 || strcmp(ci1,atual->city1)==0 || strcmp(ci2,atual->city1)==0 ||strcmp(ci3,atual->city1)==0 || strcmp(ci1,atual->city2)==0 || strcmp(ci2,atual->city2)==0 || strcmp(ci3,atual->city2)==0) {
            total++;
        }
    }
    fclose(fp);
    return total;
}


int hotPdi(Travel via,char cidade[]){
    FILE *fp = fopen("utilizadores.txt","r");
    Travel act;
    char *result,linha[MAXLINHA],*city,*hot;
    int total = 0;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        city = strtok(result,",");
        city = strtok(NULL,",");
        city = strtok(NULL,",");
        city = strtok(NULL,",");
        city = strtok(NULL,",");
        act = via;
        if (strcmp(city,cidade)==0) {
            act = via;
            hot = strtok(NULL,",");
            while(via!=NULL){
                if (strcmp(hot,act->p1)==0) {
                    total++;
                    break;
                }
                act = act->next;
            }
        }
    }
    fclose(fp);
    return total;
}


int procuraPop(char nome[]){
    FILE *fp = fopen("locais.txt","r");
    int pop=0,i=0;
    char *result, linha[MAXLINHA], *identificador, *popu,*pdi;
    while (!feof(fp)) {
        result = fgets(linha,MAXLINHA,fp);
        identificador = strtok(result,",");
        if (strcmp(identificador,"PdI")==0) {
            pdi = strtok(NULL,",");
            if (strcmp(pdi,nome)==0) {
                do{
                    result = fgets(linha,MAXLINHA,fp);
                    identificador = strtok(result,",");
                    if (strcmp(identificador,"Popularidade")==0) {
                        popu = strtok(NULL,",");
                        while (popu[i]!='\0') {
                            pop = pop * 10 +(popu[i]-'0');
                            i++;
                        }
                        break;
                    }
                }while(strcmp(identificador,"L")!=0);
                break;
            }
        }
    }
    return pop;
}


int totalPreferencias(Utilizador * atual){
    FILE *fp = fopen("utilizadores.txt","r");
    char *result,linha[MAXLINHA],*nome,*pdi11,*pdi12,*pdi13,*pdi21,*pdi22,*pdi23,*pdi32,*pdi33;
    int total = 0,i;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        nome = strtok(result,",");
        if (strcmp(nome,atual->nome)==0) {
            for(i=0;i<8;i++)
                pdi11 = strtok(NULL,",");
            pdi12 = strtok(NULL,",");
            pdi13 = strtok(NULL, ",");
            for(i=0;i<3;i++)
                pdi21 = strtok(NULL,",");
            pdi22 = strtok(NULL,",");
            pdi23 = strtok(NULL, ",");
            for(i=0;i<4;i++)
                pdi32 = strtok(NULL,",");
            pdi33 = strtok(NULL, ",");
            if (strcmp(pdi11," ")!=0 && strcmp(pdi11,"")!=0) {
                total+=procuraPop(pdi11);
            }
            if (strcmp(pdi12," ")!=0 && strcmp(pdi12,"")!=0){
                total+=procuraPop(pdi12);
            }
            if (strcmp(pdi13," ")!=0 && strcmp(pdi13,"")!=0){
                total+=procuraPop(pdi13);
            }
            if (strcmp(pdi21," ")!=0 && strcmp(pdi21,"")!=0) {
                total+=procuraPop(pdi21);
            }
            if (strcmp(pdi22," ")!=0 && strcmp(pdi22,"")!=0){
                total+=procuraPop(pdi22);
            }
            if (strcmp(pdi23," ")!=0 && strcmp(pdi23,"")!=0){
                total+=procuraPop(pdi23);
            }
            if (strcmp(pdi32," ")!=0 && strcmp(pdi32,"")!=0){
                total+=procuraPop(pdi32);
            }
            if (strcmp(pdi33," ")!=0 && strcmp(pdi33,"")!=0){
                total+=procuraPop(pdi33);
            }
            break;
        }
    }
    fclose(fp);
    return total;
}


int contaPontos(){
    FILE *fp = fopen("locais.txt","r");
    char *result,linha[MAXLINHA],*identificador,*popu;
    int total = 0,i,aux=0;
    while(!feof(fp)){
        result = fgets(linha,MAXLINHA,fp);
        identificador = strtok(result,",");
        if(strcmp(identificador,"PdI")==0){
            do{
                result = fgets(linha,MAXLINHA,fp);
                identificador = strtok(result,",");
            }while(strcmp(identificador,"Popularidade")!=0);
            if (strcmp(identificador,"Popularidade")==0) {
                aux = 0;
                popu = strtok(NULL,",");
                for (i=0; popu[i]!='\0'; i++) {
                    aux = aux * 10 +(popu[i]-'0');
                }
                total += aux;
            }
        }

    }
    fclose(fp);
    return total;
}


void print_via(Travel lista){
    Travel act;
    act = lista;
    while (act!=NULL) {
        printf("\t\t\t%s\n",act->p1);
        act  = act -> next;
    }
    printf("----------------------------------------------------------------\n");
}
