# NGC (new generation c compiler)

This language is a superset of 'c' , the goal is to compiler c projects and also we will have some cool features

# Why

As you know, There is a lot of Powerfule languages out there, Most of them have our stated goals, But C is different from any other language.
If you have worked with C a bit , You will notice the power and speed of this language . But there is a problem, Readability of C is less than High-level languages, This is obvious because it is a low level language. So NGC tries to have a low level language But to the readability and tools and capabilities of high-level languages

# Goals
- Light
- Fast
- Cross-platform
- Reliable

# Building
First Clone the project :
```
git clone https://github.com/parsa011/ngc
cd ngc
```
Now ,  You need to Run 'configure' script in scripts folder To check if the required headers are on your machine or no:
```
bash ./scripts/configure.sh
```
Tt will create a header file names config.h , Do not delete it
Now you can compiler project with make :
```
make
```
