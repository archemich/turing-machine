"use strict";
			
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

}

// Add new state
const astate = document.getElementById("astate");
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
}


// Draw Tape
const tapeSpeed = 1;
const tapeinput = document.getElementById("tapeinput");
const canvas = document.getElementById("tape");
const ctx = canvas.getContext("2d");
canvas.width = window.innerWidth;

function drawTape()
{
	let cell_size = 50;
	ctx.fillStyle = "gray";
	let space = 2;
	let middle_x = canvas.width / 2 - cell_size;
	if (tapeinput.value.length > 0)
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
		let right = middle_x ;
		ctx.fillRect(right,cell_size+space,cell_size,cell_size);
		let left = middle_x ;
		for (let i = 0; i < 3; i++)
		{
			right += cell_size + space;
			left -= cell_size + space;
			ctx.fillRect(right,cell_size+space,cell_size,cell_size);
			ctx.fillRect(left,cell_size+space,cell_size,cell_size);

		}
	
	 	ctx.fillRect(middle_x,0, cell_size,cell_size);
		ctx.fillRect(middle_x,(cell_size+space)*2, cell_size,cell_size);
}

}

tapeinput.onchange = function()
{
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	drawTape();
}

drawTape();


window.addEventListener('resize', resizeCanvas, false);
function resizeCanvas()
{
	context.clearRect(0, 0, canvas.width, canvas.height);
	canvas.width = window.innerWidth;
	drawTape();
}
