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
const itemsDisplay = document.getElementById("items-display");

// Get switch-button elements and add click event listeners

Array.from(document.getElementsByClassName("switch-button")).forEach(
    (eachButton) => {
        eachButton.addEventListener("click", () => {
            // Get the button role from the id
            const buttonRole = eachButton.id.split("-")[1];

            // print it
            console.log("button role is " + buttonRole);

            itemsDisplay!.innerHTML = buttonRole;
        });
    }
);
