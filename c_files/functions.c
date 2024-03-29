//Library definitions
#define _GNU_SOURCE
#include <stdio.h>
#include "../h_files/functions.h"
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <windows.h>


void login(){

	GetCurrentDir(buff, FILENAME_MAX);
	
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.
	//printf("%s\n", curr_dir); // Print current location.
	
	int flag = -1; // If flag = -1 => Account not found; If flag = 0 => Wrong password; Otherwise correct password.

	while(flag!=1){		
		fflush(stdin);
		clearScreen();
		header();
		footer();
		printf("\n\t\tUsuario: ");
		scanf("%s", employee.username);
		fflush(stdin);
		printf("\t\tSenha: ");
		readPassword(); // Read password using mask, COOL.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		if(strcmp(employee.username, "admin") == 0){
			flag = 1;
			strcpy(employee.name, "Administrador");
		}

		while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
			int tmp1 = strcmp(user_tmp.username, employee.username); // Check match between users.
			int tmp2 = strcmp(user_tmp.password, employee.password); // Check math between passwords.

			if(tmp1 == 0 && tmp2 == 0) // When it's true, means that the credentials are correct.
			{
				flag = 1;
				employee = user_tmp;
				break;
			}
		}

		fclose(file); // Close the file.

		char choice = '\0';
		if(flag != 1){
			printf("\n\n\t\tDesculpa! Credenciais incorrectas.\n");
			
			do{	
				printf("\n\t\tPressione:\n\t\t[1] - Tentar novamente;\n\t\t[2] - Sair.\n");
				printf("\n\t\tOpcao: ");
				scanf("%c", &choice);
				fflush(stdin);
			} while(choice!= '1' && choice != '2');
			
			flag--; // Decrease each time is entered wrong password. Once tried 3 times, the system is exited!
		}

		//printf("\nPress any KEY to continue.\n");
		if(flag<-3)
			printf("\n\t\t Excedeu o limite de tentativas.\n");
		
		if(choice == '2' || flag<-3){ 
			Exit();
		}
	}
	
	successful();

}

void mainMenu(){
	header();
	footer();
    printf("\n\t\t::: MENU PRINCIPAL :::");
    printf("\n\n\t\t[1] => Componentes:\n\t\t[2] => Posto de trabalho:\n\t\t[3] => Funcionarios:\n\t\t[4] => Operacoes:\n\t\t[5] => Empresas:\n\t\t[6] => Estatistica:\n\t\t[7] => Voltar <=::\n\t\t[8] => Sair.\n\n\t\tOperacoes: ");
    scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': Components();
        break;
        case '2': WorkOffice();
        break;
        case '3': Worker();
        break;
        case '4': Operations();
        break;
        case '5': Company();
        break;
        case '6': Statistics();
        break;
        case '7': login();
        break;
        case '8': Exit();
        break;
        default: mainMenu();
        break;
    }
}

void errorMessage(void){
	printf("\t\tFalha!\n");
}

void clearScreen(){
	system("cls");
}

// Read password using mask, COOL.
void readPassword(){
	char key = '\0';
	int index = 0;
	
	while(key != 13){
		key = getch();

		if(key != 13 && key != 8){
			putchar('*');
			employee.password[index] = key;
			index++;
		}
	}
	employee.password[index] = '\0'; // Determine the end of password.
	fflush(stdin);
}

void header(){
	system("cls");
	printf("\n");
	printf("\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb XPTO MANAGMENT SYSTEM \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
}

void footer(){
	time_t t;
	time(&t);
	printf("\n\t\tData e tempo: %s\n",ctime(&t));
}

void Exit(){
	printf("\n\t\t Ate mais! Obrigado.\n");
	exit(0);
}

void successful(){
	printf("\n\n\t\tUsuario logado com sucesso!\n\n");
	char u[20]; // It's an auxiliary variable used to print username.
	strcpy(u, employee.name);
	u[0] = toupper(u[0]);
	printf("\t\tSr(a). %s, seja bem-vindo ao XPTO MANAGEMENT SYSTEM! \n\t\tSinta-te a vontade usando o sistema ...\n\n", u);
	
	pressAnyKey();
	mainMenu();
}

void Components(){
	header();
	footer();
    printf("\n\t\t::: MENU COMPONENTES :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Substituir entre postos de trabalho:\n\t\t[5] => Listar:\n\t\t[6] => Pesquisar:\n\t\t[7] => Voltar <=::\n\t\t[8] => Sair.\n\n\t\tOperacao: ");

	scanf("%c", &choice); fflush(stdin);
	
    switch(choice)
    {
        case '1': InsertComponents();
        break;
        case '2': UpdateComponents();
        break;
        case '3': DeleteComponents();
        break;
        case '4': SubstituteByWorkOffice();
        break;
        case '5': ListComponents();
        break;
        case '6': SearchComponents();
        break;
        case '7': mainMenu();
        break;
        case '8': Exit();
        break;
        default: Components();
        break;
    }
}

void WorkOffice(){
	header();
	footer();
    printf("\n\t\t::: MENU POSTOS DE TRABALHOS :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	
	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': InsertWorkOffice();
        break;
        case '2': UpdateWorkOffice();
        break;
        case '3': DeleteWorkOffice();
        break;
        case '4': ListWorkOffice();
        break;
        case '5': SearchWorkOffice();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
        break;
        default: WorkOffice();
        break;
    }
}

void Worker(){
	header();
	footer();
    printf("\n\t\t::: MENU FUNCIONARIOS :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	
	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': InsertWorker();
        break;
        case '2': UpdateWorker();
        break;
        case '3': DeleteWorker();
        break;
        case '4': ListWorker();
        break;
        case '5': SearchWorker();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
        break;
        default: Worker();
        break;
    }
}

void Operations(){
	header();
	footer();
    printf("\n\t\t::: MENU OPERACOES :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	scanf("%c", &choice); fflush(stdin);

	
    switch(choice)
    {
        case '1': InsertOperations();
        break;
        case '2': UpdateOperations();
        break;
        case '3': DeleteOperations();
        break;
        case '4': ListOperations();
        break;
        case '5': SearchOperations();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
        break;
        default: Operations();
        break;
    }
}

void Company(){
	header();
	footer();
    printf("\n\t\t::: MENU EMPRESAS :::");    
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair:\n\n\t\tOperacoes: ");

	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': InsertCompany();
        break;
        case '2': UpdateCompany();
        break;
        case '3': DeleteCompany();
        break;
        case '4': ListCompany();
        break;
        case '5': SearchCompany();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
        break;
        default: Company();
        break;
    }
}

void InsertWorker(){
	header();
	footer();
	
	printf("\n\t\t:: INSERCAO DE FUNCIONARIO :::");
	printf("\n\n\t\tNome: ");
	gets(user_tmp.name); fflush(stdin);
	printf("\t\tNome de usuario: ");
	scanf("%s", user_tmp.username); fflush(stdin);

	while(ExistsWorker(user_tmp.username) == 1){
		printf("\n\t\tUsuario ja existente!\n");
		printf("\t\tNome de usuario: ");
		scanf("%s", user_tmp.username); fflush(stdin);
	}
	
	printf("\n\t\tFuncoes: \n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/functions.dat"; // Define directory.

	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.
	
	char read[50];
	char functions[50][100]; i = 1;
	while(fscanf(file, "%s", read) != EOF){
		strcpy(functions[i], read);
		printf("\t\t => [%d] - %s\n", i, functions[i]);;
		i++;
	}

	fclose(file);

	int option = i;

	while(option<=0 || option>=i){
		printf("\n\t\tOpcao: ");
		scanf("%d", &option); fflush(stdin);

		if(option<0 || option>=i){
			printf("\t\tOpcao invalida!\n");
		}
	} 

	strcpy(user_tmp.function, functions[option]);
	strcpy(user_tmp.password, "12345");

	printf("\n\t\tNota: ");
	gets(user_tmp.note); fflush(stdin);

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	strcpy(path, "../data/employee.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		Worker();
	}

	if(fwrite(&user_tmp, sizeof(user_tmp), 1, file))
		printf("\n\t\tFuncionario inserido com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		Worker();
	}

	fclose(file);

	pressAnyKey();
	Worker();
}

void UpdateWorker(){
	header();
	footer();
	
	printf("\n\t\t:: ATUALIZACAO DE FUNCIONARIO :::\n");
	printf("\n\t\tNome de usuario: ");
	scanf("%s", user_tmp.username); fflush(stdin);

	if(ExistsWorker(user_tmp.username) == 0){
		
		printf("\n\n\t\tUsuario inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			UpdateWorker();
		else Worker();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/employee.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct employee all_employees[MAX_ITENS];
		fread(&all_employees, sizeof(struct employee), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(strcmp(all_employees[i].username, user_tmp.username) == 0){
							
				printf("\n\n\t\tNome: ");
				gets(all_employees[i].name); fflush(stdin);

				printf("\n\t\tFuncoes: \n");

				GetCurrentDir(buff, FILENAME_MAX);
				strcpy(curr_dir, buff); 
				char path[MAX_BUF] = "../data/functions.dat"; // Define directory.

				strcat(curr_dir, path); // Make the mix.
				
				if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
					fopen(curr_dir, "w");
				else
					file = fopen(curr_dir, "r"); // Open the file.
				
				char read[50];
				char functions[50][100]; i = 1;
				while(fscanf(file, "%s", read) != EOF){
					strcpy(functions[i], read);
					printf("\t\t => [%d] - %s\n", i, functions[i]);;
					i++;
				}

				fclose(file);

				int option = i;

				while(option<=0 || option>=i){
					printf("\n\t\tOpcao: ");
					scanf("%d", &option); fflush(stdin);

					if(option<0 || option>=i){
						printf("\t\tOpcao invalida!\n");
					}
				} 

				strcpy(all_employees[i].function, functions[option]);
				printf("\n\t\tSenha: ");
				scanf("%s", all_employees[i].password); fflush(stdin);

				printf("\n\t\tNota: ");
				gets( all_employees[i].note); fflush(stdin);

				break;
			}

			if(all_employees[i].username[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "../data/employee.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_employees, sizeof(employee), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Worker();
}

void DeleteWorker(){
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE FUNCIONARIO :::\n");
	printf("\n\t\tNome de usuario: ");
	scanf("%s", user_tmp.username); fflush(stdin);

	if(ExistsWorker(user_tmp.username) == 0){
		
		printf("\n\n\t\tUsuario inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			DeleteWorker();
		else Worker();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Worker();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/employee.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct employee all_employees[MAX_ITENS];
		fread(&all_employees, sizeof(struct employee), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(strcmp(all_employees[i].username, user_tmp.username) == 0){	
				strcpy(all_employees[i].name, "");
				strcpy(all_employees[i].username, "");
				strcpy(all_employees[i].password, "");
				strcpy(all_employees[i].function, "");
				strcpy(all_employees[i].note, "");
			}

			if(all_employees[i].username[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "../data/employee.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_employees, sizeof(employee), cont + 1, file);
		printf("\n\t\tFuncionario apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Worker();
}

int ExistsWorker(char p[]){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct employee user_tmp;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
	
		if(strcmp(p, user_tmp.username) == 0)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}

int ExistsCompany(char p[]){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/company.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct company company_tmp;
	while(fread(&company_tmp, sizeof(company_tmp), 1, file) == 1){ // Search for credentials.
	
		if(strcmp(p, company_tmp.name) == 0)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}

int ExistsCompanyById(int p){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/company.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct company company_tmp;
	while(fread(&company_tmp, sizeof(company_tmp), 1, file) == 1){ // Search for credentials.
	
		if(company_tmp.id == p)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}

int ExistsComponentById(int id){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/components.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct employee component_tmp;
	while(fread(&component_tmp, sizeof(component_tmp), 1, file) == 1){ // Search for credentials.
	
		if(id == component_tmp.id)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}

int ExistsOperation(int id){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/operations.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct operations operation_tmp;
	while(fread(&operation_tmp, sizeof(operation_tmp), 1, file) == 1){ // Search for credentials.
	
		if(id == operation_tmp.id)
			flag = 1;
	}

	fclose(file); // Close the file.

	return flag;
}

void ListWorker(){
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE FUNCIONARIOS :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
		if(user_tmp.username[0] == '\0')
			continue;
		
		printf("\n\t\tNome: %s\n\t\tNome de Usuario: %s\n\t\tSenha: ****\n\t\tFuncao: %s\n\t\tNota: %s\n", 
			user_tmp.name, user_tmp.username, user_tmp.function, user_tmp.note);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	Worker();
}

void SearchWorker(){
	header();
	footer();
	
	printf("\n\t\t:: PESQUISA DE FUNCIONARIO :::\n");
	printf("\n\t\tPesquisar: ");
	char key[100];
	scanf("%s", key); fflush(stdin);
	
	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct employee user_tmp;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
		// Verify here

		int tmp1 = strcmp(key, user_tmp.username);
		int tmp2 = compare(key, user_tmp.username); // Uses WILDCARDS

		//printf("%d %d\n", tmp1, tmp2);

		if(tmp1 == 0 || tmp2 == 1){
			//Print here
			printf("\n\t\tNome: %s\n\t\tNome de Usuario: %s\n\t\tSenha: ****\n\t\tFuncao: %s\n\t\tNota: %s\n", 
				user_tmp.name, user_tmp.username, user_tmp.function, user_tmp.note);
		}
	}
	fclose(file); // Close the file.

	printf("\n");
	pressAnyKey();
	Worker();
}

void pressAnyKey(){
	printf("\t\tPressione qualquer tecla para continuar ... ");
	getch();
}

// == Components functions == //
void InsertComponents(void){

	header();
	footer();

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/components.bin"; // Define directory.
	
	printf("\n\t\t:: INSERCAO DE COMPONENTE :::");
	printf("\n\n\t\tID: ");
	scanf("%d", &company_tmp.id); fflush(stdin);

	printf("\t\tNome: ");
	gets(component_tmp.name); fflush(stdin);

	printf("\t\tNumero de serie: ");
	scanf("%s", component_tmp.serie_number); fflush(stdin);
	datetaken:
	printf("\t\tData de aquisicao: ");
	scanf("%s", component_tmp.date_taken); fflush(stdin);
	if(validate(component_tmp.date_taken)==0)
	{
		printf("\t\tDIGITE UMA DATA VALIDA: ");
		goto datetaken;
	}
	printf("\t\tDias de garantia: ");
	scanf("%d", &component_tmp.guarantee); fflush(stdin);

	printf("\t\tID do fornecedor: ");
	scanf("%d", &component_tmp.id_supplier); fflush(stdin);

	printf("\t\tID do Fabricante: ");
	scanf("%d", &component_tmp.id_maker); fflush(stdin);
	
	printf("\t\tTipo de componente: ");
	scanf("%d", &component_tmp.type); fflush(stdin);
	
	printf("\t\tCondicao: ");
	scanf("%d", &component_tmp.status); fflush(stdin);

	printf("\t\tID do Posto de Trabalho: ");
	scanf("%d", &component_tmp.id_work_office); fflush(stdin);

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	strcpy(path, "../data/components.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		WorkOffice();
	}

	if(fwrite(&component_tmp, sizeof(component_tmp), 1, file))
		printf("\n\t\tComponente inserido com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		WorkOffice();
	}

	fclose(file);

	pressAnyKey();
	Components();
}

void UpdateComponents(void){
	header();
	footer();
	
	printf("\n\t\t:: ATUALIZACAO DE COMPONENTE :::\n");
	printf("\n\t\tId do Componente: ");
	scanf("%d", &component_tmp.id); fflush(stdin);

	if(ExistsComponentById(component_tmp.id) == 0){
		
		printf("\n\n\t\tComponente inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			UpdateComponents();
		else Components();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/components.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct components all_components[MAX_ITENS];
		fread(&all_components, sizeof(struct components), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_components[i].id == component_tmp.id){
							
				printf("\t\tNome: ");
				gets(component_tmp.name); fflush(stdin);

				printf("\t\tNumero de serie: ");
				scanf("%s", component_tmp.serie_number); fflush(stdin);
				datetaken1:
				printf("\t\tData de aquisicao: ");
				scanf("%s", component_tmp.date_taken); fflush(stdin);
					if(validate(component_tmp.date_taken)==0)
					{		
					printf("\t\tDIGITE UMA DATA VALIDA: ");
					goto datetaken1;
					}
				printf("\t\tDias de garantia: ");
				scanf("%d", &component_tmp.guarantee); fflush(stdin);

				printf("\t\tID do fornecedor: ");
				scanf("%d", &component_tmp.id_supplier); fflush(stdin);

				printf("\t\tID do Fabricante: ");
				scanf("%d", &component_tmp.id_maker); fflush(stdin);

				printf("\t\tTipo de componente: ");
				scanf("%d", &component_tmp.type); fflush(stdin);

				printf("\t\tCondicao: ");
				scanf("%d", &component_tmp.status); fflush(stdin);

				printf("\t\tID do Posto de Trabalho: ");
				scanf("%d", &component_tmp.id_work_office); fflush(stdin);

				break;
			}

			if(all_components[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "../data/components.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_components, sizeof(component_tmp), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Components();
}

void DeleteComponents(void){
	
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE COMPONENTES :::\n");
	printf("\n\t\tId do Componente: ");
	scanf("%d", &component_tmp.id); fflush(stdin);

	if(ExistsComponentById(component_tmp.id) == 0){
		
		printf("\n\n\t\tComponente inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			DeleteComponents();
		else Components();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Components();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/components.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct components all_components[MAX_ITENS];
		fread(&all_components, sizeof(struct components), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_components[i].id == component_tmp.id){	
				strcpy(all_components[i].name, "");
			}

			if(all_components[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "../data/components.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_components, sizeof(component_tmp), cont + 1, file);
		printf("\n\t\tComponente apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Components();
}

void ListComponents(void){
	
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE COMPONENTES :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/components.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&component_tmp, sizeof(component_tmp), 1, file) == 1){ // Search for credentials.
		if(component_tmp.name[0] == '\0')
			continue;
		
		printf("\n\t\tId: %d\n\t\tDesignacao: %s\n\t\tNumero de Serie: %s\n\t\tData de aquisicao: %s\n\t\tDias de Garantia: %d\n\t\tId do Fornecedor: %d\n\t\tId do Fabricador: %d\n\t\tTipo: %d\n\t\tCondicao: %d\n\t\tId do Posto de Trabalho: %d\n", 
			component_tmp.id, component_tmp.name, component_tmp.serie_number, component_tmp.date_taken, component_tmp.guarantee, component_tmp.id_supplier, component_tmp.id_maker, component_tmp.type, component_tmp.status, component_tmp.id_work_office);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	Components();
}

void SearchComponents(void){
	header();
	footer();
	
	printf("\n\t\t:: PESQUISA DE COMPONENTES :::\n");
	printf("\n\t\tPesquisar: ");
	char key[100];
	scanf("%s", key); fflush(stdin);
	
	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/components.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct components component_tmp;
	while(fread(&component_tmp, sizeof(component_tmp), 1, file) == 1){ // Search for credentials.
		// Verify here

		int tmp1 = strcmp(key, component_tmp.name);
		int tmp2 = compare(key, component_tmp.name); // Uses WildCards

		if(tmp1 == 0 || tmp2 == 1){
			//Print here
			printf("\n\t\tId: %d\n\t\tDesignacao: %s\n\t\tNumero de Serie: %s\n\t\tData de aquisicao: %s\n\t\tDias de Garantia: %d\n\t\tId do Fornecedor: %d\n\t\tId do Fabricador: %d\n\t\tTipo: %d\n\t\tCondicao: %d\n\t\tId do Posto de Trabalho: %d\n", 
				component_tmp.id, component_tmp.name, component_tmp.serie_number, component_tmp.date_taken, component_tmp.guarantee, component_tmp.id_supplier, component_tmp.id_maker, component_tmp.type, component_tmp.status, component_tmp.id_work_office);
		
		}
	}
	fclose(file); // Close the file.

	printf("\n");
	pressAnyKey();
	Components();
}

void SubstituteByWorkOffice(){
	header();
	footer();
	
	printf("\n\t\t:: SUBSTITUICAO DE COMPONENTES ENTRE POSTOS DE TRABALHO :::\n");
	printf("\n\t\tId do Componente: ");
	scanf("%d", &component_tmp.id); fflush(stdin);

	if(ExistsComponentById(component_tmp.id) == 0){
		
		printf("\n\n\t\tComponente inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			SubstituteByWorkOffice();
		else Components();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/components.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct components all_components[MAX_ITENS];
		fread(&all_components, sizeof(struct components), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_components[i].id == component_tmp.id){
							
				printf("\t\tId do Posto de Trabalho Actual: %s\n", all_components[i].id_work_office);

				printf("\t\tId Novo Posto de Trabalho: ");
				int id_new;
				scanf("%d", &id_new); fflush(stdin);

				if(ExistsComponentById(id_new) == 0){
		
					printf("\n\n\t\tComponente inexistente!\n");
					printf("\n\t\tTentar novamente ? Sim/Nao: ");
					scanf("%c", &choice);
					fflush(stdin);

					choice = toupper(choice);

					if(choice == 'S')
						SubstituteByWorkOffice();
					else Components();
				} else{
					all_components[i].id_work_office = id_new;
				}


				break;
			}

			if(all_components[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "../data/components.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_components, sizeof(component_tmp), cont + 1, file);
		printf("\n\t\tPosto de Trabalho substituido com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Components();
}

int ExistsComponent(char p[]){
	return 0;
}

// == WorkOffice functions == //
void InsertWorkOffice(void){
	header();
	footer();
	
	printf("\n\t\t:: INSERCAO DE POSTO DE TRABALHO :::");
	printf("\n\n\t\tNome do Posto de Trabalho: ");
	gets(work_office_tmp.name); fflush(stdin);

	while(ExistsWorkOffice(work_office_tmp.name) == 1){
		printf("\n\t\tPosto de Trabalho ja existente!\n");
		printf("\t\tNome do Posto de Trabalho: ");
		scanf("%s", work_office_tmp.name); fflush(stdin);
	}

	printf("\n\t\tLocal: ");
	gets(work_office_tmp.place); fflush(stdin);

	printf("\n\t\tSeccao: ");
	scanf("%d", &work_office_tmp.section); fflush(stdin);
	
	printf("\n\t\tNota: ");
	gets(work_office_tmp.note); fflush(stdin);

	printf("\n\t\tIdentificacao do Funcionario: ");
	scanf("%d", &work_office_tmp.id_employee); fflush(stdin);

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	
	char path[MAX_BUF] = ""; // Define directory.
	strcpy(path, "../data/work_office.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		WorkOffice();
	}

	if(fwrite(&work_office_tmp, sizeof(work_office_tmp), 1, file))
		printf("\n\t\tPosto de Trabalho inserido com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		Worker();
	}

	fclose(file);

	pressAnyKey();
	WorkOffice();
}

void UpdateWorkOffice(void){
	header();
	footer();
	
	printf("\n\t\t::: ATUALIZACAO DE POSTOS DE TRABALHO :::\n");
	printf("\n\t\tNome do Posto de Trabalho: ");
	scanf("%d", &work_office_tmp.name); fflush(stdin);

	if(ExistsWorkOffice(work_office_tmp.name) == 0){
		
		printf("\n\n\t\tPosto de Trabalho inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			UpdateWorkOffice();
		else WorkOffice();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/work_office.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct work_office all_work_offices[MAX_ITENS];
		fread(&all_work_offices, sizeof(struct work_office), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_work_offices[i].id == work_office_tmp.id){
							
				printf("\t\tNome: ");
				gets(all_work_offices[i].name); fflush(stdin);

				printf("\n\t\tLocal: ");
				gets(all_work_offices[i].place); fflush(stdin);

				printf("\n\t\tSeccao: ");
				scanf("%d", &all_work_offices[i].section); fflush(stdin);

				printf("\n\t\tNota: ");
				gets(all_work_offices[i].note); fflush(stdin);

				break;
			}

			if(all_work_offices[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "../data/work_office.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_work_offices, sizeof(work_office_tmp), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	WorkOffice();
}

void DeleteWorkOffice(void){
	
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE POSTO DE TRABALHO :::\n");
	printf("\n\t\tId do Posto de Trabalho: ");
	scanf("%d", &work_office_tmp.id); fflush(stdin);

	if(ExistsComponentById(work_office_tmp.id) == 0){
		
		printf("\n\n\t\tPosto de Trabalo inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			DeleteComponents();
		else Components();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Components();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/work_office.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct work_office all_work_offices[MAX_ITENS];
		fread(&all_work_offices, sizeof(struct work_office), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_work_offices[i].id == work_office_tmp.id){	
				strcpy(all_work_offices[i].name, "");
			}

			if(all_work_offices[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "../data/work_office.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_work_offices, sizeof(work_office_tmp), cont + 1, file);
		printf("\n\t\tPosto de Trabalho apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	WorkOffice();
}

void ListWorkOffice(void){
	
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE POSTOS DE TRABALHO :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/work_office.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&work_office_tmp, sizeof(struct work_office), 1, file) == 1){ // Search for credentials.
		if(work_office_tmp.name[0] == '\0')
			continue;
		
		printf("\n\t\tId: %d\n\t\tNome: %s\n\t\tLugar: %s\n\t\tSeccao: %d\n\t\tNota: %s\n\t\tId do Funcionario: %d\n", 
			work_office_tmp.id, work_office_tmp.name, work_office_tmp.place, work_office_tmp.section, work_office_tmp.note, work_office_tmp.id_employee);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	WorkOffice();
}

void SearchWorkOffice(void){
	header();
	footer();
	
	printf("\n\t\t:: PESQUISA DE POSTO DE TRABALHO :::\n");
	printf("\n\t\tPesquisar: ");
	char key[100];
	scanf("%s", key); fflush(stdin);
	
	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/work_office.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct work_office work_office_tmp;
	while(fread(&work_office_tmp, sizeof(work_office_tmp), 1, file) == 1){ // Search for credentials.
		// Verify here

		int tmp1 = strcmp(key, work_office_tmp.name);
		int tmp2 = compare(key, work_office_tmp.name); // Uses WildCards

		if(tmp1 == 0 || tmp2 == 1){
			//Print here
		
			printf("\n\t\tId: %d\n\t\tNome: %s\n\t\tLugar: %s\n\t\tSeccao: %s\n\t\tNota: %d\n\t\tId do Funcionario: %d\n", 
				work_office_tmp.id, work_office_tmp.name, work_office_tmp.place, work_office_tmp.section, work_office_tmp.note, work_office_tmp.id_employee);
		
		}
	}
	fclose(file); // Close the file.

	printf("\n");
	pressAnyKey();
	WorkOffice();
}

int ExistsWorkOffice(char p[]){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/work_office.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct company company_tmp;
	while(fread(&company_tmp, sizeof(company_tmp), 1, file) == 1){ // Search for credentials.
	
		if(strcmp(p, company_tmp.name) == 0)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}

// Operations functions
void InsertOperations(void){

	header();
	footer();

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/operations.bin"; // Define directory.
	
	printf("\n\t\t:: INSERCAO DE OPERACOES :::");
	printf("\n\n\t\tID: ");
	scanf("%d", &operation_tmp.id); fflush(stdin);

	printf("\n\n\t\tId do Documento Interno: ");
	scanf("%d", &operation_tmp.id_internal_doc); fflush(stdin);

	printf("\n\n\t\tId do Documento Externo: ");
	scanf("%d", &operation_tmp.id_external_doc); fflush(stdin);

	printf("\n\n\t\tId do Componente: ");
	scanf("%d", &operation_tmp.id_component); fflush(stdin);

	printf("\n\n\t\tId da Empresa: ");
	scanf("%d", &operation_tmp.id_company); fflush(stdin);

	printf("\n\n\t\tTipo: ");
	scanf("%d", &operation_tmp.type); fflush(stdin);
	
	printf("\n\n\t\tData de Entrada: ");
	scanf("%s", operation_tmp.date_in); fflush(stdin);

	printf("\n\n\t\tData de Saida: ");
	scanf("%s", operation_tmp.date_out); fflush(stdin);

	printf("\n\n\t\tData de Previsao de Entrada: ");
	scanf("%s", operation_tmp.date_prevision_in); fflush(stdin);
	
	printf("\n\n\t\tId do Funcionario: ");
	scanf("%d", &operation_tmp.id_employee); fflush(stdin);
	date:
	printf("\n\n\t\tData: ");
	scanf("%s", operation_tmp.date); fflush(stdin);
	if(validate(operation_tmp.date)==0)
	{
		printf("\t\tDIGITE UMA DATA VALIDA: ");
		goto date;
	}
	printf("\n\n\t\tMontante: ");
	scanf("%f", &operation_tmp.money); fflush(stdin);
	
	printf("\n\n\t\tObservacoes: ");
	gets(operation_tmp.observation); fflush(stdin);

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	strcpy(path, "../data/operations.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		WorkOffice();
	}

	if(fwrite(&component_tmp, sizeof(component_tmp), 1, file))
		printf("\n\t\tOperacao inserida com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		Operations();
	}

	fclose(file);

	pressAnyKey();
	Operations();
}

void UpdateOperations(void){
	header();
	footer();
	
	printf("\n\t\t::: ATUALIZACAO DE OPERACOES :::\n");
	printf("\n\t\tId da Operacao: ");
	scanf("%d", &operation_tmp.id); fflush(stdin);

	if(ExistsOperation(operation_tmp.id) == 0){
		
		printf("\n\n\t\tOperacao inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			UpdateOperations();
		else Operations();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/operations.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct operations all_operations[MAX_ITENS];
		fread(&all_operations,  sizeof(struct operations), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_operations[i].id == operation_tmp.id){
							
				printf("\n\n\t\tId do Documento Interno: ");
				scanf("%d", &all_operations[i].id_internal_doc); fflush(stdin);

				printf("\n\n\t\tId do Documento Externo: ");
				scanf("%d", &all_operations[i].id_external_doc); fflush(stdin);

				printf("\n\n\t\tId do Componente: ");
				scanf("%d", &all_operations[i].id_component); fflush(stdin);

				printf("\n\n\t\tId da Empresa: ");
				scanf("%d", &all_operations[i].id_company); fflush(stdin);

				printf("\n\n\t\tTipo: ");
				scanf("%s", all_operations[i].type); fflush(stdin);
				datein:
				printf("\n\n\t\tData de Entrada: ");
				scanf("%s", all_operations[i].date_in); fflush(stdin);
				if(validate(all_operations[i].date_in)==0)
				{
					printf("\t\tINSIRA UMA DATA VALIDA:");goto datein;	
				}
				dateout:
				printf("\n\n\t\tData de Saida: ");
				scanf("%s", all_operations[i].date_out); fflush(stdin);
				if(validate(all_operations[i].date_out)==0)
				{			
				printf("\t\tDIGITE UMA DATA VALIDA: ");
				goto dateout;
				}
				dateprev:
				printf("\n\n\t\tData de Previsao de Entrada: ");
				scanf("%s", all_operations[i].date_prevision_in); fflush(stdin);
				if(validate(all_operations[i].date_precision_in)==0)
				{	
				printf("\t\tDIGITE UMA DATA VALIDA: ");
				goto dateprev;
				}
				printf("\n\n\t\tId do Funcionario: ");
				scanf("%d", &all_operations[i].id_employee); fflush(stdin);
				datex:
				printf("\n\n\t\tData: ");
				scanf("%s", all_operations[i].date); fflush(stdin);
				if(validate(all_operations[i].date)==0)
				{
				printf("\t\tDIGITE UMA DATA VALIDA: ");
				goto datex;
				}
				printf("\n\n\t\tMontante: ");
				scanf("%f", &all_operations[i].money); fflush(stdin);

				printf("\n\n\t\tObservacoes: ");
				gets(all_operations[i].observation); fflush(stdin);
				break;
			}

			if(all_operations[i].id_internal_doc != -1)
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "../data/operations.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_operations, sizeof(operation_tmp), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Operations();
}

void DeleteOperations(void){
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE OPERACOES :::\n");
	printf("\n\t\tId da Operacao: ");
	scanf("%d", &operation_tmp.id); fflush(stdin);

	if(ExistsOperation(operation_tmp.id) == 0){
		
		printf("\n\n\t\tOperacao inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			DeleteOperations();
		else Operations();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Components();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/operations.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct operations all_operations[MAX_ITENS];
		fread(&all_operations, sizeof(struct operations), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_operations[i].id == operation_tmp.id){	
				all_operations[i].id_external_doc = -1;
			}

			if(all_operations[i].id_internal_doc != -1)
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "../data/operation.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_operations, sizeof(operation_tmp), cont + 1, file);
		printf("\n\t\tOperacao apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Operations();
}

void ListOperations(void){
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE OPERACOES :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/operations.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&operation_tmp, sizeof(struct operations), 1, file) == 1){ // Search for credentials.
		if(operation_tmp.id_internal_doc == -1 || operation_tmp.id_external_doc == -1) 
			continue;
		
		printf("\n\t\tId: %d\n\t\tId do Documento Interno: %d\n\t\tId do Documento Externo: %d\n\t\tId do Posto de Trabalho: %d\n\t\tId do Componente: %d\n\t\tId da Empresa: %d\n\t\tTipo de Operacao: %d\n\t\tData de Saida: %s\n\t\tData de Chegada: %s\n\t\tData Prevista de Chegada: %s\n\t\tId do Funcionario Responsavel: %d\n\t\tData da Operacao: %s\n\t\tMontante: %f\n\t\tObservacoes: %s\n", 
			operation_tmp.id, operation_tmp.id_internal_doc, operation_tmp.id_external_doc, 
			operation_tmp.id_work_office, operation_tmp.id_component, operation_tmp.id_company, 
			operation_tmp.type, operation_tmp.date_out, operation_tmp.date_in, 
			operation_tmp.date, operation_tmp.id_employee, operation_tmp.date, 
			operation_tmp.money, operation_tmp.observation);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	Operations();
}

void SearchOperations(void){
	header();
	footer();
	
	printf("\n\t\t:: PESQUISA DE OPERACOES :::\n");
	printf("\n\t\tPesquisar: ");
	int key;
	scanf("%d", key); fflush(stdin);
	
	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/operations.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct operations operation_tmp;
	while(fread(&operation_tmp, sizeof(operation_tmp), 1, file) == 1){ // Search for credentials.
		// Verify here
		if(operation_tmp.id == key){
			//Print here
			
		printf("\n\t\tId: %d\n\t\tId do Documento Interno: %d\n\t\tId do Documento Externo: %d\n\t\tId do Posto de Trabalho: %d\n\t\tId do Componente: %d\n\t\tId da Empresa: %d\n\t\tTipo de Operacao: %d\n\t\tData de Saida: %s\n\t\tData de Chegada: %s\n\t\tData Prevista de Chegada: %s\n\t\tId do Funcionario Responsavel: %d\n\t\tData da Operacao: %s\n\t\tMontante: %f\n\t\tObservacoes: %s\n", 
			operation_tmp.id, operation_tmp.id_internal_doc, operation_tmp.id_external_doc, 
			operation_tmp.id_work_office, operation_tmp.id_component, operation_tmp.id_company, 
			operation_tmp.type, operation_tmp.date_out, operation_tmp.date_in, 
			operation_tmp.date, operation_tmp.id_employee, operation_tmp.date, 
			operation_tmp.money, operation_tmp.observation);
		}
	}
	fclose(file); // Close the file.

	printf("\n");
	pressAnyKey();
	WorkOffice();
}

// == Company functions == //
void InsertCompany(void){
	
	header();
	footer();
	
	printf("\n\t\t::: INSERCAO DE EMPRESA :::");
	printf("\n\n\t\tNome: ");
	gets(company_tmp.name); fflush(stdin);

	while(ExistsCompany(company_tmp.name) == 1){
		printf("\n\t\tEmpresa ja existente!\n");
		printf("\t\tNome da Empresa: ");
		scanf("%s", company_tmp.name); fflush(stdin);
	}

	printf("\t\tTipo: ");
	scanf("%s", company_tmp.type); fflush(stdin);

	printf("\t\tContacto: ");
	scanf("%s", company_tmp.contact); fflush(stdin);

	char path[MAX_BUF] = "../data/company.bin"; // Define directory.

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	strcpy(path, "../data/company.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		Company();
	}

	if(fwrite(&company_tmp, sizeof(struct company), 1, file))
		printf("\n\t\tEmpresa inserida com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		Company();
	}

	fclose(file);

	pressAnyKey();
	Company();
}

void UpdateCompany(void){
	header();
	footer();
	
	printf("\n\t\t:: ATUALIZACAO DE EMPRESA :::\n");
	printf("\n\t\tNome da Empresa: ");
	scanf("%d", &company_tmp.name); fflush(stdin);

	if(ExistsCompany(company_tmp.name) == 0){
		
		printf("\n\n\t\tEmpresa inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			UpdateCompany();
		else Company();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/company.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct company all_companies[MAX_ITENS];
		fread(&all_companies, sizeof(company_tmp), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_companies[i].id == company_tmp.id){
							
				printf("\t\tNome: ");
				gets(company_tmp.name); fflush(stdin);

				printf("\t\tTipo: ");
				scanf("%s", company_tmp.type); fflush(stdin);

				printf("\t\tContacto: ");
				scanf("%s", company_tmp.contact); fflush(stdin);

				break;
			}

			if(all_companies[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "../data/company.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_companies, sizeof(company_tmp), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Components();
}

void DeleteCompany(void){
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE EMPRESA :::\n");
	printf("\n\t\tId da Empresa: ");
	scanf("%d", &company_tmp.id); fflush(stdin);

	if(ExistsCompanyById(company_tmp.id) == 0){
		
		printf("\n\n\t\tEmpresa inexistente!\n");
		printf("\n\t\tTentar novamente ? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

 		if(choice == 'S')
			DeleteCompany();
		else Company();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Company();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/company.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct company all_companies[MAX_ITENS];
		fread(&all_companies, sizeof(struct company), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_companies[i].id == company_tmp.id){	
				strcpy(all_companies[i].name, "");
				DeleteCompanyFromOperations(all_companies[i].id);
			}

			if(all_companies[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "../data/company.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_companies, sizeof(company_tmp), cont + 1, file);
		printf("\n\t\tEmpresa apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Company();
}

void DeleteCompanyFromOperations(int id_company){

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "../data/operations.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct operations all_operations[MAX_ITENS];
		fread(&all_operations, sizeof(struct operations), MAX_ITENS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_ITENS; i++){
			if(all_operations[i].id_company == id_company){	
				all_operations[i].id_company = -1;
			}

			if(all_operations[i].id_company != -1)
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "../data/operation.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_operations, sizeof(operation_tmp), cont + 1, file);
		fclose(file);
}

void ListCompany(void){
	
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE EMPRESA :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/company.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&company_tmp, sizeof(struct company), 1, file) == 1){ // Search for credentials.
		if(company_tmp.name[0] == '\0')
			continue;
		
		printf("\n\t\tId: %d\n\t\tNome: %s\n\t\tTipo: %s\n\t\tContacto: %s\n", 
			company_tmp.id, company_tmp.name, company_tmp.type, company_tmp.contact);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	Company();
}

void SearchCompany(void){
	
	header();
	footer();
	
	printf("\n\t\t:: PESQUISA DE EMPRESAS :::\n");
	printf("\n\t\tPesquisar: ");
	char key[100];
	scanf("%s", key); fflush(stdin);
	
	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "../data/company.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct company company_tmp;
	while(fread(&company_tmp, sizeof(company_tmp), 1, file) == 1){ // Search for credentials.
		// Verify here

		int tmp1 = strcmp(key, company_tmp.name);
		int tmp2 = compare(key, company_tmp.name); // Uses WildCards

		if(tmp1 == 0 || tmp2 == 1){
			//Print here
			printf("\n\t\tId: %d\n\t\tNome: %s\n\t\tTipo: %s\n\t\tContacto: %s\n", 
				company_tmp.id, company_tmp.name, company_tmp.type, company_tmp.contact);
		}
	}
	fclose(file); // Close the file.

	printf("\n");
	pressAnyKey();
	Company();
}


// == Statistic functions == //
void Statistics(void){
	header();
	footer();
	
	printf("\n\t\t::: ESTATISTICAS :::");
	printf("\n\n\t\tTotal de Funcionarios: %d;\n", 12);
	printf("\n\t\tTotal de Operacoes feitas: %d;\n", 40);
	printf("\n\t\tComponente mais vendido: %d\n", 6);
	printf("\n\t\tOperacao mais cara: %d\n", 2);
	printf("\n\t\tNumero de vendas nos ultimos 3 meses: %d\n", 12);
	printf("\n\t\tMelhor fornecedor: %d\n", 9);
	printf("\n\t\tFuncionario que mais atendeu: %d\n", 34);
	printf("\n\t\tPercentagem de ganho: %2.f%\n", 60.00);
	printf("\n\t\tMelhor duracao saida e chegada de produtos: %d\n\n", 60.00);

	printf("\n\t\tDeseja voltar? Sim/Nao: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'S')
			mainMenu();
		else Exit();
}

// == WildCard feature == //

// Using Dynamic Programming
int searchWildCard(char text[], char key[], int n, int m){
	// Code goes here
	// Empty text can only math with empty key
	if(m == 0)
		return (n == 0);

	//Lookup table for storing results of sub-problems
	int dp[n+1][m+1];
	
	//Initialize lookup table to to false
	memset(dp, 0, sizeof(dp));

	//Empty text can math with empty key
	dp[0][0] = 1;

	//Only '*' can math with empty key
	for (j = 1; j<=m; j++)
		if(key[j-1] == '*')
			dp[0][j] = dp[0][j-1];

	//Fill the table in bottom-up manner
	for (i = 1; i<=n; i++)
		for (j = 1; j<=m; j++)
			// There are two cases if we find a '*'
			// a) We ignore '*' character and move
			// 	to next character in the text,
			// i.e., '*' indicates an empty sequence.
			// b) '*' character matches with ith character in key

 			if(key[j-1] == '*')
				dp[i][j] = dp[i][j-1] || dp[i-1][j];
			else 
				if(key[j-1] == '?' || text[i-1] == key[j-1])
					dp[i][j] = dp[i-1][j-1];

			// If characters don't match
			else 
				dp[i][j] = 0;

	return dp[n][m];
}

// Using pointers
int searchWildCard_v2(char *first, char * second)
{
    // If we reach at the end of both strings, we are done
    if (*first == '\0' && *second == '\0')
        return 1;
  
    // Make sure that the characters after '*' are present
    // in second string. This function assumes that the first
    // string will not contain two consecutive '*'
    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return 0;
  
    // If the first string contains '?', or current characters
    // of both strings match
    if (*first == '?' || *first == *second)
        return searchWildCard_v2(first+1, second+1);
  
    // If there is *, then there are two possibilities
    // a) We consider current character of second string
    // b) We ignore current character of second string.
    if (*first == '*')
        return searchWildCard_v2(first+1, second) || searchWildCard_v2(first, second+1);
        
    return 0;
}
  
// A function to run test cases
int compare(char *first, char *second)
{  searchWildCard_v2(first, second)? 1: 0; }

// A function to validate the date
int validate(char *date)
{
int tmp=0,tmp1=0,tmp2=0,flag=0;
if(strlen(date)<=10){
tmp=(date[0]-'0')*10+(date[1] - '0');
if(tmp > 0 && tmp <32) flag++;
tmp1=(date[3]-'0')*10+(date[4]-'0');
if(tmp1 > 0 && tmp1 <13) flag++;
tmp2=(((date[6]-'0')*10+(date[7]-'0'))*10+(date[8]-'0'))*10+(date[9]-'0');
if(tmp2 > 2000) flag++;
}
return flag==3 ? 1 : 0;

}
