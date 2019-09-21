'use strict';
const functions = require('firebase-functions');

const admin = require('firebase-admin');
admin.initializeApp();

exports.lamp_on = functions.https.onRequest(async (req, res) => {
  return admin.database().ref('/room/lamp_status').set(1);
});

exports.lamp_off = functions.https.onRequest(async (req, res) => {
    return admin.database().ref('/room/lamp_status').set(0);
  });