function modInverse(a, m) {
  a = ((a % m) + m) % m;
  for (let x = 1; x < m; x++) if ((a * x) % m === 1) return x;
  return 1;
}

function affineEncrypt() {
  let text = document.getElementById("affineText").value.toUpperCase();
  let a = parseInt(document.getElementById("affineA").value);
  let b = parseInt(document.getElementById("affineB").value);
  let res = "";

  for (let ch of text) {
    if (/[A-Z]/.test(ch)) {
      let x = ch.charCodeAt(0) - 65;
      res += String.fromCharCode(((a * x + b) % 26) + 65);
    } else res += ch;
  }
  document.getElementById("affineResult").innerText = res;
}

function affineDecrypt() {
  let text = document.getElementById("affineText").value.toUpperCase();
  let a = parseInt(document.getElementById("affineA").value);
  let b = parseInt(document.getElementById("affineB").value);
  let a_inv = modInverse(a, 26);
  let res = "";

  for (let ch of text) {
    if (/[A-Z]/.test(ch)) {
      let y = ch.charCodeAt(0) - 65;
      res += String.fromCharCode(((a_inv * (y - b + 26)) % 26) + 65);
    } else res += ch;
  }
  document.getElementById("affineResult").innerText = res;
}
