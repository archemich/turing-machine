"use strict";

function sleep(milliseconds) {
  const date = Date.now();
  let currentDate = null;
  do {
    currentDate = Date.now();
} while (currentDate - date < milliseconds);
return;
}

//////////////Table Of Rules control/////////////////////////////////
// Add new symbol
const asym = document.getElementById("asym");
asym.onclick = function()
{
    let table = document.getElementById("table_rules");
    let rlength = table.rows[0].length;
    let ncell = table.rows[0].insertCell(rlength);
    ncell.className = "spectd";
    ncell.innerHTML = "<input type=\"text\ class=\"symbol\">";
    for(let i = 1; i < table.rows.length; i++)
    {
        let a = table.rows[i].insertCell(rlength);
        a.innerHTML = "<input type=\"text\" class=\"rule\">";
    }
    return;
}


// Remove last symbol
const rsym = document.getElementById("rsym");
rsym.onclick = function()
{
    let table = document.getElementById("table_rules");
    let cellindex = table.rows[0].cells.length - 1;
    if (cellindex > 1)
    {
        for(let i = 0; i < table.rows.length; i++)
        {
            table.rows[i].deleteCell(cellindex);
        }
    }
    else alert("You can't delete more cells");
    return;
}

// Add new state
const astate = document.getElementById("astate");
astate.onclick = function()
{
    let table = document.getElementById("table_rules");
    let rc = table.rows.length;
    let nrow = table.insertRow(rc);
    let cell = nrow.insertCell(0);
    cell.className = "state";
    cell.innerHTML = `q${rc}`;
    for (let i = 1; i < table.rows[0].cells.length; i++)
    {
        let ncell = nrow.insertCell(i);
        ncell.innerHTML = "<input type=\"text\" class=\"rule\">"
    }
    return;
}

// Remove last state
const rstate = document.getElementById("rstate");
rstate.onclick = function()
{
    let table = document.getElementById("table_rules");
    let rc = table.rows.length;
    if (rc > 2)
    {
        table.deleteRow(rc-1);
    }
    else alert("You can't delete more rows");
    return;
}


//////////////////////// Turing Machine /////////////////////////
const charset = ['L','N','R'];

const tapeinput = document.getElementById("tapeinput");
const run = document.getElementById("run");
const temptape = document.getElementById("temptape");
let alphabet = [];
let states = [];
let rules = [];
let tape;

function getInput()
{
    tape = tapeinput.value.split("");
    let table = document.getElementById("table_rules");
    for (let i = 1; i < table.rows[0].cells.length; i++)
    {
        alphabet.push(table.rows[0].cells[i].getElementsByTagName("input")[0].value);
    }

    for (let i = 0; i < table.rows.length; i++)
    {
        states.push(i);
    }

    for (let i = 1; i < table.rows.length; i++)
    {
        rules[i] = [];
        for (let j = 1; j < table.rows[0].cells.length; j++)
        {
            rules[i][j-1] = table.rows[i].cells[j].getElementsByTagName("input")[0].value;
        }
    }
    console.debug("Alphabet is", alphabet);
    console.debug("States are", states);
    console.debug("Rules are:", rules);
    return;
}

function clearInput()
{
    temptape.innerHTML = '_____';
    alphabet = [];
    states = [];
    rules = [];
    return;
}

function updateTape(newtape)
{
    temptape.innerHTML = newtape.join('');
    return;
}

run.onclick = function()
{
    // Input
    clearInput();
    getInput();

    let checkAlphabet = function()
    {

        for (let i = 0; i < alphabet.length; i++)
        {

            if (alphabet[i].length > 1)
            {
                console.error(`\'${alphabet[i]}\' is not allowed. You must use only  one character.`);
                alert(`\'${alphabet[i]}\' is not allowed. You must use only one character.`);
                return false;
            }
        }
        return true;
    }

    let checkTape = function()
    {
        for (let i = 0; i < tape.length; i++)
        {
            if (alphabet.indexOf(tape[i]) == -1)
            {
                console.error(`Symbol \'${tape[i]}\' is not declared in alphabet.`);
                alert(`Symbol \'${tape[i]}\' is not declared in alphabet.`);
                return false;
            }
        }
        return true;
    }

    let checkRules = function()
    {
        let sym;
        let mov;
        let state;
        let rule;
        for (let i = 1; i < rules.length; i++)
        {
            for (let j = 0; j < rules[i].length; j++)
            {
                rule = rules[i][j];
                if (rule != '-')
                {
                    sym = rules[i][j][0];
                    mov = rules[i][j][1];
                    state = rules[i][j].slice(2);

                    if (alphabet.indexOf(sym) == -1)
                    {
                        console.error(`Symbol \'${sym}\' is not declared in alphabet.`);
                        alert(`Symbol \'${sym}\' is not declared in alphabet.`);
                        return false;
                    }
                    else if (charset.indexOf(mov) == -1)
                    {
                        console.error(`Symbol \'${mov}\' is not allowed.`)
                        alert(`Symbol \'${mov}\' is not allowed. You can use only \'L\', \'N\' or \'R\'.`)
                        return false;
                    }
                    else if(state[0] != 'q')
                    {
                        console.error(`You have to use 'q' before state number.`);
                        alert(`You have to use 'q' before state number.`);
                        return false;
                    }
                    else if (states.indexOf(Number(state.slice(1))) == -1)
                    {
                        console.error(`\'${state}\' is not declared.`);
                        alert(`\'${state}\' is not declared.`);
                        return false;
                    }
                }
            }
        }
        return true;
    }


    // Check input in general
    if (!checkAlphabet() || !checkTape() || !checkRules())
        return;

    //Turing Machine start
    const endless_cycle_limit = 400;  // Endless cycle protection
    let loop = 0;                     // Endless cycle protection
    let rule;
    let state = 1;
    let last_state = 0;               // Endless cycle protection
    let RWH = 0;
    let mov;
    let newsym;
    while(state != 0)
    {
        rule = rules[state][alphabet.indexOf(tape[RWH])];
        if (rule != '-')
        {
            newsym = rule[0];
            mov = rule[1];
            last_state = state;
            state = rule.slice(3);
            loop = (last_state == state) ? loop + 1 : 0;
            tape[RWH] = newsym;
            switch (mov) {
                case 'L': RWH--; if(tape[RWH] == undefined) tape[RWH] = '_'; break;
                case 'R': RWH++; if(tape[RWH] == undefined) tape[RWH] = '_'; break;
            }
        }
        else
        {
            alert('error');
        }
        if (loop > endless_cycle_limit)
        {
            alert('Looks like your program got into an endless loop');
            break;
        }
        
    }
    updateTape(tape);
    return;
}