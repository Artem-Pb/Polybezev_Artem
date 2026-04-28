package com.github.Artem_Pb.service;

import com.github.Artem_Pb.domain.MegaTask;
import com.github.Artem_Pb.domain.SimpleTask;
import com.github.Artem_Pb.domain.Status;
import com.github.Artem_Pb.domain.Task;
import com.github.Artem_Pb.exception.InvalidTaskOperationException;
import com.github.Artem_Pb.exception.TaskNotFoundException;
import com.github.Artem_Pb.repository.MegaTaskRepository;
import com.github.Artem_Pb.repository.SimpleTaskRepository;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.test.util.ReflectionTestUtils;

import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

// @ExtendWith(MockitoExtension.class) — запускает тест через Mockito без Spring.
// Быстро: нет ApplicationContext, нет базы, нет HTTP.
@ExtendWith(MockitoExtension.class)
class TaskServiceImplTest {

    // @Mock создаёт фиктивный объект. Все его методы по умолчанию возвращают null / пустые коллекции.
    @Mock
    private SimpleTaskRepository simpleTaskRepository;

    @Mock
    private MegaTaskRepository megaTaskRepository;

    // @InjectMocks создаёт реальный TaskServiceImpl и вставляет в него моки выше через конструктор.
    @InjectMocks
    private TaskServiceImpl taskService;

    // --- createTask ---

    @Test
    void createTask_withBlankTitle_throwsInvalidTaskOperationException() {
        // assertThatThrownBy — AssertJ способ проверить что метод бросает исключение.
        assertThatThrownBy(() -> taskService.createTask("   "))
                .isInstanceOf(InvalidTaskOperationException.class);
    }

    @Test
    void createTask_withValidTitle_savesAndReturnsTask() {
        SimpleTask saved = new SimpleTask("Buy milk");
        // when(...).thenReturn(...) — "когда вызовут этот метод с этим аргументом — верни вот это".
        // any(SimpleTask.class) — матчит любой SimpleTask, нам не важен конкретный объект.
        when(simpleTaskRepository.save(any(SimpleTask.class))).thenReturn(saved);

        SimpleTask result = taskService.createTask("Buy milk");

        assertThat(result.getTitle()).isEqualTo("Buy milk");
        assertThat(result.getStatus()).isEqualTo(Status.NOT_STARTED);
        // verify — проверяет что метод был вызван ровно один раз.
        verify(simpleTaskRepository).save(any(SimpleTask.class));
    }

    // --- getById ---

    @Test
    void getById_notFound_throwsTaskNotFoundException() {
        when(simpleTaskRepository.findById(99L)).thenReturn(Optional.empty());
        when(megaTaskRepository.findById(99L)).thenReturn(Optional.empty());

        assertThatThrownBy(() -> taskService.getById(99L))
                .isInstanceOf(TaskNotFoundException.class);
    }

    @Test
    void getById_simpleTaskExists_returnsIt() {
        SimpleTask task = new SimpleTask("Read book");
        when(simpleTaskRepository.findById(1L)).thenReturn(Optional.of(task));

        Task result = taskService.getById(1L);

        assertThat(result).isEqualTo(task);
        // Если нашли в simpleRepo — megaRepo не должны трогать.
        verify(megaTaskRepository, never()).findById(any());
    }

    // --- updateStatus ---

    @Test
    void updateStatus_setsNewStatus() {
        SimpleTask task = new SimpleTask("Walk dog");
        when(simpleTaskRepository.findById(1L)).thenReturn(Optional.of(task));

        taskService.updateStatus(1L, Status.COMPLETED);

        assertThat(task.getStatus()).isEqualTo(Status.COMPLETED);
    }

    // --- updateSubTaskStatus + автоматическое обновление родителя ---

    @Test
    void updateSubTaskStatus_allComplete_parentBecomesCompleted() {
        MegaTask mega = new MegaTask("Sprint");
        SimpleTask sub1 = new SimpleTask("Task A");
        SimpleTask sub2 = new SimpleTask("Task B");
        // ReflectionTestUtils.setField — устанавливает приватное поле без сеттера.
        // Нужно потому что id присваивает JPA, у нас нет setId().
        ReflectionTestUtils.setField(sub1, "id", 1L);
        ReflectionTestUtils.setField(sub2, "id", 2L);
        mega.addSubTask(sub1);
        mega.addSubTask(sub2);
        sub1.setStatus(Status.COMPLETED); // первый уже завершён

        when(simpleTaskRepository.findById(10L)).thenReturn(Optional.empty());
        when(megaTaskRepository.findById(10L)).thenReturn(Optional.of(mega));

        // Завершаем второй сабтаск — теперь оба COMPLETED → родитель должен стать COMPLETED.
        taskService.updateSubTaskStatus(10L, 2L, Status.COMPLETED);

        assertThat(mega.getStatus()).isEqualTo(Status.COMPLETED);
    }

    @Test
    void updateSubTaskStatus_someComplete_parentBecomesInProgress() {
        MegaTask mega = new MegaTask("Sprint");
        SimpleTask sub1 = new SimpleTask("Task A");
        SimpleTask sub2 = new SimpleTask("Task B");
        ReflectionTestUtils.setField(sub1, "id", 1L);
        ReflectionTestUtils.setField(sub2, "id", 2L);
        mega.addSubTask(sub1);
        mega.addSubTask(sub2);

        when(simpleTaskRepository.findById(10L)).thenReturn(Optional.empty());
        when(megaTaskRepository.findById(10L)).thenReturn(Optional.of(mega));

        // Завершаем только первый — один из двух готов → IN_PROGRESS.
        taskService.updateSubTaskStatus(10L, 1L, Status.COMPLETED);

        assertThat(mega.getStatus()).isEqualTo(Status.IN_PROGRESS);
    }

    // --- deleteTask ---

    @Test
    void deleteTask_simpleTask_deletesFromSimpleRepository() {
        SimpleTask task = new SimpleTask("Clean");
        when(simpleTaskRepository.findById(1L)).thenReturn(Optional.of(task));

        taskService.deleteTask(1L);

        verify(simpleTaskRepository).deleteById(1L);
        // never() — гарантируем что megaRepo не трогали вообще.
        verify(megaTaskRepository, never()).deleteById(any());
    }

    @Test
    void deleteTask_megaTask_deletesFromMegaRepository() {
        MegaTask mega = new MegaTask("Big project");
        when(simpleTaskRepository.findById(5L)).thenReturn(Optional.empty());
        when(megaTaskRepository.findById(5L)).thenReturn(Optional.of(mega));

        taskService.deleteTask(5L);

        verify(megaTaskRepository).deleteById(5L);
        verify(simpleTaskRepository, never()).deleteById(any());
    }

    // --- updateTitle ---

    @Test
    void updateTitle_withBlankTitle_throwsException() {
        assertThatThrownBy(() -> taskService.updateTitle(1L, ""))
                .isInstanceOf(InvalidTaskOperationException.class);
    }
}
