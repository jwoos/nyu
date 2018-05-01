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

	populateEvaluations: async () => {
		const response = await fetch(`${BASE}/students/${window.student.account.id}/evaluations`, {
			method: 'GET',
			headers: {'Authorization': window.student.token}
		});

		if (response.status === 401) {
			window.common.notAuthenticated();
			return;
		}

		const data = await response.json();

		const evalTag = document.querySelector('#evaluations');

		for (const val of data.data) {
			const card = document.createElement('div');
			card.className = 'card';

			const header = document.createElement('div');
			header.className = 'card-header';
			header.innerText = `${val.name} (${val.semester}-${val.year})`;

			const body = document.createElement('div');
			body.className = 'card-body';

			const text = document.createElement('div');
			text.className = 'card-text';

			text.innerText = `Rating: ${val.rating}\nComments: ${val.comments}`;

			body.appendChild(text);
			card.appendChild(header);
			card.appendChild(body);

			evalTag.appendChild(card);
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
	switch (window.location.pathname) {
		case '/student/evaluation.html':
			document.querySelector('#submit').addEventListener('click', window.student.submit);
			await window.student.populateEnrollments();
			break;

		case '/student/history.html':
			await window.student.populateEvaluations();
			break;
	}
	
	document.querySelector("#logOut").addEventListener('click',function(){
		window.common.clearToken();
		window.common.clearAccount();
		window.location.replace('/');
	});
});
