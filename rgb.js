var color = require("rgb")


var deviceId = process.argv[2];
var split = color(process.argv[3]).split("(")[1].split(")")[0].split(",");

var red = parseInt(split[0]);
var green = parseInt(split[1]);
var blue = parseInt(split[2]);


console.log(red, green, blue);
var deviseOff =  (deviceId * 10);

var deviseOn =  deviseOff + 1;

var redStateLow = deviseOn * 1000;
var redStateHigh = redStateLow + 255;
var greenStateLow = redStateHigh + 1;
var greenStateHigh = greenStateLow + 255;

var blueStateLow = greenStateHigh + 1;
//var blueStateHigh = blueStateLow + 255;


var redState = redStateLow + red;
var greenState = greenStateLow + green;
var blueState = blueStateLow + blue;


const spawn = require('child_process').spawn;

function sendCode(state) {
    const send = spawn('sudo', ['/home/irfn/433Utils/RPi_utils/codesend', state]);


    send.stdout.on('data', function (data) {
        console.log("stdout:" + data);
    });
}
sendCode(redState);
sendCode(greenState);
sendCode(blueState);