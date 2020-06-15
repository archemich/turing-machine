"use strict";
			
//////////////Table Of Rules control/////////////////////////////////
// Add new symbol
let asym = document.getElementById("asym");
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
	
}

// Remove last symbol
let rsym = document.getElementById("rsym");
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

}

// Add new state
let astate = document.getElementById("astate");
astate.onclick = function()
{
	let table = document.getElementById("table_rules");
	let rc = table.rows.length;
	let nrow = table.insertRow(rc);
	let cell = nrow.insertCell(0);
	cell.className = "spectd";
	cell.innerHTML = `q${rc}`;
	for (let i = 1; i < table.rows[0].cells.length; i++)
	{
		let ncell = nrow.insertCell(i);
		ncell.innerHTML = "<input type=\"text\" class=\"rule\">"
	}
}

// Remove last state
let rstate = document.getElementById("rstate");
rstate.onclick = function()
{
	let table = document.getElementById("table_rules");
	let rc = table.rows.length;
	if (rc > 2)
	{
	table.deleteRow(rc-1);
	}
	else alert("You can't delete more rows");
}


// Draw Tape
const tapeSpeed = 1;
let tapeinput = document.getElementById("tapeinput");
let canvas = document.getElementById("tape");
let ctx = canvas.getContext("2d");
function drawTape()
{
	
	ctx.fillStyle = "green";
	if (tapeinput.value.length > 3)
	{
		let prev = -50;

		for (let i = 0; i < tapeinput.value.length; i++)
		{
			prev += 50;
			ctx.fillRect(prev,0,50,50);	
		}
		
	} 
	else 
	{
	
		let prev = -50;
		for (let i = 0; i < 3; i++)
		{
			prev += 50;
			ctx.fillRect(prev,0,50,50);	
		}
	}

}

tapeinput.onchange = function()
{
	drawTape();
}
drawTape();

window.addEventListener('resize', resizeCanvas, false);
function resizeCanvas()
{
	canvas.width = window.innerWidth;
	drawTape();
}
