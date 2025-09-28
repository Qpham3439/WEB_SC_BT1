function process(text, key, mode) {
    text = text.toUpperCase().replace(/[^A-Z]/g, '');
    key = key.toUpperCase();
    let res = '';
    for (let i = 0, j = 0; i < text.length; i++) {
        let c = text.charCodeAt(i) - 65;
        let k = key.charCodeAt(j % key.length) - 65;
        if (mode === 'enc') res += String.fromCharCode(((c + k) % 26) + 65);
        else res += String.fromCharCode(((c - k + 26) % 26) + 65);
        j++;
    }
    return res;
}

function encrypt() {
    let text = document.getElementById('plaintext').value;
    let key = document.getElementById('key').value;
    document.getElementById('result').innerText = process(text, key, 'enc');
}

function decrypt() {
    let text = document.getElementById('plaintext').value;
    let key = document.getElementById('key').value;
    document.getElementById('result').innerText = process(text, key, 'dec');
}