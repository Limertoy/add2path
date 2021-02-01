#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winreg.h>
#include <dir.h>

void zmienPath(char *envir, char *nazwa, char *tekst){ 
	HKEY hkey = 0; 
	DWORD dword1;
	if (RegCreateKeyEx (HKEY_CURRENT_USER, envir,
		0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, &dword1
) != ERROR_SUCCESS)
		return;
	RegSetValueEx (hkey, nazwa, 0, REG_SZ, (BYTE *) tekst, strlen (tekst) + 1);
	RegCloseKey (hkey);
}

char *zabracLinie(char *tekst, char *linia){
	size_t len = strlen(linia);
	if (len > 0){
		char *p = tekst;
		while ((p = strstr(p, linia)) != NULL){
			memmove(p, p + len, strlen(p + len) + 1);
		}
	}
	return tekst;
}


int main(){
	int n;
	printf("1 - add to system path current folder\n");
	printf("2 - operation with absolute path\n");
	printf("3 - operation with relative path\n");
	printf("Podaj opcje: \n");
	scanf("%d", &n);
	getchar();
	char sciezkaPath[1024], cwd[255];
	DWORD rozmiar = 1024;
	RegGetValue(HKEY_CURRENT_USER, "Environment", "Path", RRF_RT_ANY, NULL, (PVOID)&sciezkaPath, &rozmiar);
	switch (n)
	{
	case 1:
		getcwd(cwd, 100); 
		strcat(cwd, ";"); 
		if(strstr(sciezkaPath, cwd)){ 
			zabracLinie(sciezkaPath, cwd);
			zmienPath("Environment", "Path", sciezkaPath);
			printf("Current folder deleted from PATH.\n");
			printf("PATH=%s", sciezkaPath);
		} else {
			strcat(sciezkaPath, cwd);
			zmienPath("Environment", "Path", sciezkaPath);
			printf("Current folder added to PATH.\n");
			printf("PATH=%s", sciezkaPath);
		}
		break;
	case 2:
		printf("Input absolute path: ");
		scanf("%s", cwd);
		strcat(cwd, ";");
		if(strstr(sciezkaPath, cwd)){
			zabracLinie(sciezkaPath, cwd);
			zmienPath("Environment", "Path", sciezkaPath);
			printf("Folder deleted from PATH.\n");
			printf("PATH=%s", sciezkaPath);
		} else {
			strcat(sciezkaPath, cwd);
			zmienPath("Environment", "Path", sciezkaPath);
			printf("Folder added to PATH.\n");
			printf("PATH=%s", sciezkaPath);
		}
		break;
	case 3:
		printf("Input relative path: ");
		char cwd1[255];
		scanf("%s", cwd1); 
		getcwd(cwd, sizeof cwd);
		strcat(cwd, cwd1);
		strcat(cwd, ";");
		if(strstr(sciezkaPath, cwd)){
			zabracLinie(sciezkaPath, cwd);
			zmienPath("Environment", "Path", sciezkaPath);
			printf("Folder deleted from PATH.\n");
			printf("PATH=%s", sciezkaPath);
		} else {
			strcat(sciezkaPath, cwd);
			zmienPath("Environment", "Path", sciezkaPath);
			printf("Folder added to PATH.\n");
			printf("PATH=%s", sciezkaPath);
		}
		break;
	default: 
		printf("Error: Bad option.");
	}	
}
