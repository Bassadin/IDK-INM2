# Task 09 IDK Bastian Hodapp

## Test Data

I used ChatGPT to generate a sample `.xml` file. The file is located in `src/data/` and is called `data.xml`.

My prompt was: `Write an .xml file with 10 addresses including, as data fields: name, surname, street, house number, PLZ, city, telephone number, email address, birthday`
Unfortunately, ChatGPT only generated 5 addresses, but that should be enough to start.

## Project setup

I used the `vanilla-ts` starter package from <https://vitejs.dev/guide/> to create a baseline JS project.
I'm using the JS class `XSLTProcessor` to parse the `.xml` and `.xsl` files into HTML.

## XSL files

I created the three XSL files in `src/styles/`: `simple.xsl`, `table.xsl` and `fancy.xsl`.

## Webpage

On the webpage, you can choose between the three XSL files using the buttons in the header.
The webpage is located in `src/index.html`, but needs to be built into a package first with `yarn build`.
