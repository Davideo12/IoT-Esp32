const socket = io();

const btnOn = document.getElementById('on');
const btnOff = document.getElementById('off');

btnOn.addEventListener('click', () => {
    socket.emit('on', {state: 'HIGH'});
});

btnOff.addEventListener('click', () => {
    socket.emit('off', {state: 'LOW'});
});