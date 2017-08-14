'use strict';

const $username = $('input[type="text"]');
const $password = $('input[type="password"]');
const $userLabel = $('label[for="username"]');
const $passLabel = $('label[for="password"]');

$username.on('focus', function() {
	if (!$(this).hasClass('is-filled')) {
		$userLabel.addClass('is-filled');
	}
});

$password.on('focus', function() {
	if (!$(this).hasClass('is-filled')) {
		$passLabel.addClass('is-filled');
	}
});

$username.on('blur', function() {
	if ($(this).val()) {
		$(this).addClass('is-filled');
	} else {
		$(this).removeClass('is-filled');
		$userLabel.removeClass('is-filled');
	}
});

$password.on('blur', function() {
	if ($(this).val()) {
		$(this).addClass('is-filled');
	} else {
		$(this).removeClass('is-filled');
		$passLabel.removeClass('is-filled');
	}
});

$('button').on('click', function(event) {
	event.preventDefault();

	let usernameValue = $username.val();
	let passwordValue = $password.val();

	if (usernameValue && passwordValue) {
		$.post('/', {
			username: usernameValue,
			password: passwordValue
		}, function(data) {
			if (data) {
				alert(data);
			} else {
				window.location = '/user';
			}
		});
	} else {
		alert('Both fields must be filled out!');
	}
});
