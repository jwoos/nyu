'use strict';

window.common.checkAuthentication(false);

window.student = {
	token: window.common.getToken(),
	account: window.common.getAccount(),

	populateEnrollments: async () => {
		const response = await fetch(`${BASE}/students/${window.student.account.id}/enrollments`, {
			method: 'GET',
			headers: {'Authorization': window.student.token}
		});

		if (response.status === 401) {
			window.common.notAuthenticated();
			return;
		}

		const data = await response.json();

		const selectTag = document.querySelector('#courses');

		for (const val of data.data) {
			const optionTag = document.createElement('option');
			optionTag.setAttribute('data-value', JSON.stringify(val));
			optionTag.innerText = `${val.name} (${val.semester}-${val.year})`;
			selectTag.appendChild(optionTag);
		}
	},

	submit: async () => {
		const options = document.querySelector('#courses').options;
		const value = JSON.parse(options[options.selectedIndex].getAttribute('data-value'));

		if (!value) {
			return;
		}

		const body = {
			enrollment_id: value.id,
			rating: parseInt(document.querySelector('#rating').value),
			comments: document.querySelector('#comments').value
		};

		const response = await fetch(`${BASE}/evaluations`, {
			method: 'POST',
			headers: {'Content-Type': 'application/json', 'Authorization': window.student.token},
			body: JSON.stringify(body)
		});

		if (response.status == 201) {
			alert('Submitted');
			window.location.reload();
		} else {
			const err = await response.json();
			console.error(err);
		}
	}
};

window.addEventListener('load', async () => {
	const account = window.common.getAccount();
	document.querySelector('#unumber').innerText = account.university_number;

	document.querySelector('#submit').addEventListener('click', window.student.submit);

	await window.student.populateEnrollments();
});
