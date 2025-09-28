function shiftChar(ch, k) {
  if (/[A-Z]/.test(ch)) {
    return String.fromCharCode((ch.charCodeAt(0) - 65 + k + 26) % 26 + 65);
  }
  if (/[a-z]/.test(ch)) {
    return String.fromCharCode((ch.charCodeAt(0) - 97 + k + 26) % 26 + 97);
  }
  return ch;
}

function getKey() {
  const val = parseInt(document.getElementById("caesarKey").value, 10);
  return isNaN(val) ? 0 : val;
}

function caesarEncrypt() {
  const text = document.getElementById("caesarText").value;
  const k = getKey();
  const res = Array.from(text).map(ch => shiftChar(ch, k)).join("");
  document.getElementById("caesarResult").innerText = res;
}

function caesarDecrypt() {
  const text = document.getElementById("caesarText").value;
  const k = getKey();
  const res = Array.from(text).map(ch => shiftChar(ch, -k)).join("");
  document.getElementById("caesarResult").innerText = res;
}

function caesarClear() {
  document.getElementById("caesarText").value = "";
  document.getElementById("caesarResult").innerText = "";
}
