function generatePlayfairKey(key) {
  key = key.toUpperCase().replace(/J/g, "I").replace(/[^A-Z]/g, "");
  let seen = new Set(), table = [];

  for (let ch of key) if (!seen.has(ch)) { seen.add(ch); table.push(ch); }
  for (let i = 0; i < 26; i++) {
    let ch = String.fromCharCode(65 + i);
    if (ch === "J") continue;
    if (!seen.has(ch)) { seen.add(ch); table.push(ch); }
  }
  return table;
}

function prepareText(text) {
  text = text.toUpperCase().replace(/J/g, "I").replace(/[^A-Z]/g, "");
  let res = "";
  for (let i = 0; i < text.length; i++) {
    res += text[i];
    if (i < text.length - 1 && text[i] === text[i + 1]) res += "X";
  }
  if (res.length % 2) res += "X";
  return res;
}

function playfairProcess(text, key, decrypt = false) {
  let table = generatePlayfairKey(key);
  let res = "";
  text = prepareText(text);

  for (let i = 0; i < text.length; i += 2) {
    let a = text[i], b = text[i + 1];
    let idxA = table.indexOf(a), idxB = table.indexOf(b);
    let rowA = Math.floor(idxA / 5), colA = idxA % 5;
    let rowB = Math.floor(idxB / 5), colB = idxB % 5;

    if (rowA === rowB) {
      colA = (colA + (decrypt ? 4 : 1)) % 5;
      colB = (colB + (decrypt ? 4 : 1)) % 5;
    } else if (colA === colB) {
      rowA = (rowA + (decrypt ? 4 : 1)) % 5;
      rowB = (rowB + (decrypt ? 4 : 1)) % 5;
    } else {
      let tmp = colA;
      colA = colB;
      colB = tmp;
    }
    res += table[rowA * 5 + colA];
    res += table[rowB * 5 + colB];
  }
  return res;
}

function playEncrypt() {
  let t = document.getElementById("playText").value;
  let k = document.getElementById("playKey").value;
  document.getElementById("playResult").innerText = playfairProcess(t, k, false);
}

function playDecrypt() {
  let t = document.getElementById("playText").value;
  let k = document.getElementById("playKey").value;
  document.getElementById("playResult").innerText = playfairProcess(t, k, true);
}
