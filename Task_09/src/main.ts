import "./style.scss";

document.querySelector<HTMLDivElement>("#app")!.innerHTML = `
  <div>
    <button class="switch-button" id="show-simple" type="button">Simple</button>
    <button class="switch-button" id="show-table" type="button">Table</button>
    <button class="switch-button" id="show-fancy" type="button">Fancy</button>


    <div id="items-display">
    </div>
  </div>
`;

// Get the items display element
const itemsDisplayElement = document.getElementById("items-display");

// Get switch-button elements and add click event listeners

Array.from(document.getElementsByClassName("switch-button")).forEach(
    (eachButton) => {
        eachButton.addEventListener("click", () => {
            // Get the button role from the id
            const buttonRole = eachButton.id.split("-")[1];

            // print it
            console.log("button role is " + buttonRole);

            itemsDisplayElement!.innerHTML = buttonRole;

            let xsltProcessor = new XSLTProcessor();

            // Load the xslt file, example1.xsl
            let styleRequest = new XMLHttpRequest();
            styleRequest.open("GET", `styles/${buttonRole}.xsl`, false);
            styleRequest.send(null);

            let xslStylesheet = styleRequest.responseXML;

            xsltProcessor.importStylesheet(xslStylesheet!);

            // Load the XML file, example1.xml
            let dataRequest = new XMLHttpRequest();
            dataRequest.open("GET", "data/data.xml", false);
            dataRequest.send(null);

            let xmlDataDoc = dataRequest.responseXML;

            const fragment = xsltProcessor.transformToFragment(
                xmlDataDoc!,
                document
            );
            itemsDisplayElement!.textContent = "";
            itemsDisplayElement!.appendChild(fragment);
        });
    }
);
