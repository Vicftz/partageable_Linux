#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <string>


static int functionCalcul(int a, int b, std::string compo)
{
        int (*func)(int,int);
        int result = 0;
        void *handle;
       
        if(compo.compare("Composant2")==0)
                handle = dlopen("./libComposant2.so", RTLD_LAZY);
        else
                 handle = dlopen("./libComposant1.so", RTLD_LAZY);
        if(handle == NULL)
        {
                printf("erreur lors du dlopen : %s\n", dlerror());
                exit(EXIT_FAILURE);
        }

        if(compo.compare("Composant2") == 0)
        {
                *(void **) (&func) = dlsym(handle, "composant2");
               
                if (func == NULL)
                {
                        printf("Error occured");
                        printf("erreur dlsym : %s\n", dlerror());
                        dlclose(handle);
                        exit(EXIT_FAILURE);
                }

                result = func(a,b);
        }
        else
        {
                *(void **) (&func) = dlsym(handle, "composant1");
                
                if (func == NULL)
                {
                        printf("Error occured");
                        printf("erreur dlsym : %s\n", dlerror());
                        dlclose(handle);
                        exit(EXIT_FAILURE);
                }

                result = func(a,b);
        }
        // Fermeture de la bibliothèque
        dlclose(handle);

        return result;
}
int main(int argc, char ** argv)
{
    if(argc != 4) exit(EXIT_FAILURE);
	int data1 = std::stoi(argv[2]);
	int data2 = std::stoi(argv[3]);

	int valeur=0;
        std::cout << argc << " " << argv[1];
        if(argc == 4)
        {
                std::string arg1(argv[1]);
                //std::cout << std::endl << "In the loop " << arg1;
                if((arg1.compare("Composant1") == 0) || (arg1.compare("Composant2") == 0)) 
                {
                        valeur = functionCalcul(data1, data2, arg1);
                }
        }

        std::cout << std::endl;
	std::cout << "Résultat :" << valeur << std::endl;
}
