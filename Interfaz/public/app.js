const socket = io();

const btnOn = document.getElementById('on');
const btnOff = document.getElementById('off');

socket.on('ready', data => {
    console.log(data);
})

btnOn.addEventListener('click', () => {
    socket.emit('on', {state: 'HIGH'});
});

btnOff.addEventListener('click', () => {
    socket.emit('off', {state: 'LOW'});
});