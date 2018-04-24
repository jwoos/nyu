'use strict';

window.common.checkAuthentication(false);

window.professor = {
	token: window.common.getToken(),
	account: window.common.getAccount(),

	populateCourses: async () => {
		const response = await fetch(`${BASE}/professors/${window.professor.account.id}/courses`, {
			method: 'GET',
			headers: {'Authorization': window.professor.token}
		});

		if (response.status === 401) {
			window.common.notAuthenticated();
			return;
		}

		const data = await response.json();

		for (const val of data.data) {
			console.log(val);
		}
	},

	populateEvaluations: async () => {
		const response = await fetch(`${BASE}/professors/${window.professor.account.id}/evaluations`, {
			method: 'GET',
			headers: {'Authorization': window.professor.token}
		});

		if (response.status === 401) {
			window.common.notAuthenticated();
			return;
		}

		const data = await response.json();

		for (const val of data.data) {
			console.log(val);
		}
	},
};

window.addEventListener('load', async () => {
	switch (window.location.pathname) {
		case '/professor/history.html':
			await window.student.populateEvaluations();
			break;
	}
});
